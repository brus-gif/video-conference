#include "SignalingClient.h"
#include "protocol.h"

#include <QJsonArray>
#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonParseError>
#include <QUrl>
#include <QWebSocket>

SignalingClient::SignalingClient(QObject *parent)
    : QObject(parent)
    , m_socket(new QWebSocket())
{
    connect(m_socket, &QWebSocket::connected, this, &SignalingClient::onConnected);
    connect(m_socket, &QWebSocket::textMessageReceived, this, &SignalingClient::onTextMessage);
    connect(m_socket, &QWebSocket::binaryMessageReceived, this, &SignalingClient::onBinaryMessage);
    connect(m_socket, &QWebSocket::disconnected, this, &SignalingClient::onDisconnected);
    // 连接阶段出错（连不上/握手失败）时上报，方便界面提示
    connect(m_socket, &QWebSocket::errorOccurred, this, [this](QAbstractSocket::SocketError) {
        if (!isConnected())
            emit errorOccurred(QStringLiteral("connect_failed"), m_socket->errorString());
    });
}

SignalingClient::~SignalingClient()
{
    m_socket->abort();
    delete m_socket;
}

bool SignalingClient::isConnected() const
{
    return m_socket->state() == QAbstractSocket::ConnectedState;
}
//返回当前房间id
QString SignalingClient::roomId() const { return m_roomId; }
//返回本机在会议中的id
QString SignalingClient::selfId() const { return m_selfId; }
//连接服务器
void SignalingClient::connectToServer(const QString &url)
{
    m_roomId.clear();
    m_selfId.clear();
    m_socket->open(QUrl(url));
}

void SignalingClient::disconnectFromServer()
{
    m_roomId.clear();
    m_selfId.clear();
    m_socket->close();
}

// ---------------------------------------------------------------------------
// 协议操作-----客户端->服务器
// ---------------------------------------------------------------------------

void SignalingClient::createRoom(const QString &name)
{
    QJsonObject obj;
    obj[QLatin1String(Protocol::KeyType)] = QLatin1String(Protocol::C2S::CreateRoom);
    obj[QLatin1String(Protocol::KeyName)] = name;
    sendJson(obj);
}

void SignalingClient::joinRoom(const QString &roomId, const QString &name)
{
    QJsonObject obj;
    obj[QLatin1String(Protocol::KeyType)] = QLatin1String(Protocol::C2S::JoinRoom);
    obj[QLatin1String(Protocol::KeyRoomId)] = roomId;
    obj[QLatin1String(Protocol::KeyName)] = name;
    sendJson(obj);
}

void SignalingClient::leaveRoom()
{
    QJsonObject obj;
    obj[QLatin1String(Protocol::KeyType)] = QLatin1String(Protocol::C2S::LeaveRoom);
    sendJson(obj);
}

void SignalingClient::setState(bool mic, bool cam)
{
    QJsonObject obj;
    obj[QLatin1String(Protocol::KeyType)] = QLatin1String(Protocol::C2S::SetState);
    obj[QLatin1String(Protocol::KeyMic)] = mic;
    obj[QLatin1String(Protocol::KeyCam)] = cam;
    sendJson(obj);
}

void SignalingClient::setShare(bool on)
{
    QJsonObject obj;
    obj[QLatin1String(Protocol::KeyType)] = QLatin1String(Protocol::C2S::SetShare);
    obj[QLatin1String(Protocol::KeyOn)] = on;
    sendJson(obj);
}

void SignalingClient::sendChat(const QString &text)
{
    QJsonObject obj;
    obj[QLatin1String(Protocol::KeyType)] = QLatin1String(Protocol::C2S::Chat);
    obj[QLatin1String(Protocol::KeyText)] = text;
    sendJson(obj);
}

void SignalingClient::ping()
{
    QJsonObject obj;
    obj[QLatin1String(Protocol::KeyType)] = QLatin1String(Protocol::C2S::Ping);
    sendJson(obj);
}
//meta里面存放媒体附属信息（视频 / 音频）  payload里面放真实的二进制数据
void SignalingClient::sendMedia(const QJsonObject &meta, const QByteArray &payload)
{
    if (!isConnected())
        return;
    m_socket->sendBinaryMessage(packEnvelope(meta, payload));
}

// ---------------------------------------------------------------------------
// 服务端消息解析
// ---------------------------------------------------------------------------

void SignalingClient::onConnected()
{
    emit connected();
}

void SignalingClient::onDisconnected()
{
    m_roomId.clear();
    m_selfId.clear();
    emit disconnected();
}

void SignalingClient::onBinaryMessage(const QByteArray &data)
{
    QJsonObject header;
    QByteArray payload;
    if (!unpackEnvelope(data, header, payload))
        return;

    const QString kind = header.value(QLatin1String(Protocol::KeyKind)).toString();//媒体类型( video | audio | screen)
    const QString senderId = header.value(QLatin1String(Protocol::KeyMemberId)).toString();//发送方的成员 ID
    if (kind.isEmpty())
        return;
    emit mediaFrameReceived(kind, senderId, payload, header);
}
//QWebSocket 文本消息的接收槽函数
void SignalingClient::onTextMessage(const QString &message)
{
    QJsonParseError err{};
    const QJsonDocument doc = QJsonDocument::fromJson(message.toUtf8(), &err);
    if (err.error != QJsonParseError::NoError || !doc.isObject())
        return;
    const QJsonObject obj = doc.object();
    const QString type = obj.value(QLatin1String(Protocol::KeyType)).toString();

    if (type == QLatin1String(Protocol::S2C::Hello))
    {
        // 建连问候，无需处理
    } 
    else if (type == QLatin1String(Protocol::S2C::RoomCreated)) 
    {//客户端请求创建房间之后服务端回复
        m_roomId = obj.value(QLatin1String(Protocol::KeyRoomId)).toString();
        emit roomCreated(m_roomId);
    }
    else if (type == QLatin1String(Protocol::S2C::Joined )) 
    {//客户端请求进房间，服务端回复
        m_roomId = obj.value(QLatin1String(Protocol::KeyRoomId)).toString();//房间id
        m_selfId = obj.value(QLatin1String(Protocol::KeyMemberId)).toString();//成员id
        QVector<Member> members;//获取参会人员的成员id
        const QJsonArray arr = obj.value(QLatin1String(Protocol::KeyMembers)).toArray();
        members.reserve(arr.size());
        for (const QJsonValue &v : arr)
            members.append(parseMember(v.toObject()));
        emit joined(m_roomId, m_selfId, members);
    }
    else if (type == QLatin1String(Protocol::S2C::MemberJoined))
    {//新成员加入房间
        emit memberJoined(parseMember(obj.value(QLatin1String(Protocol::KeyMember)).toObject()));
    }
    else if (type == QLatin1String(Protocol::S2C::MemberLeft))
    {//有成员退出房间
        emit memberLeft(obj.value(QLatin1String(Protocol::KeyMemberId)).toString());
    }
    else if (type == QLatin1String(Protocol::S2C::MemberUpdated)) 
    {//某个成员状态变更（麦克风、摄像头、屏幕共享）
        emit memberUpdated(obj.value(QLatin1String(Protocol::KeyMemberId)).toString(),
                           obj.value(QLatin1String(Protocol::KeyMic)).toBool(),
                           obj.value(QLatin1String(Protocol::KeyCam)).toBool(),
                           obj.value(QLatin1String(Protocol::KeySharing)).toBool());
    } 
    else if (type == QLatin1String(Protocol::S2C::Chat))
    {//聊天消息
        emit chatMessage(obj.value(QLatin1String(Protocol::KeyMemberId)).toString(),
                         obj.value(QLatin1String(Protocol::KeyName)).toString(),
                         obj.value(QLatin1String(Protocol::KeyText)).toString());
    }
    else if (type == QLatin1String(Protocol::S2C::RoomClosed)) 
    {//房间被关闭
        m_roomId.clear();
        emit roomClosed();
    } 
    else if (type == QLatin1String(Protocol::S2C::Error))
    {//业务错误包
        emit errorOccurred(obj.value(QLatin1String(Protocol::KeyCode)).toString(),
                           obj.value(QLatin1String(Protocol::KeyMessage)).toString());
    }
    else if (type == QLatin1String(Protocol::S2C::Pong)) 
    {//心跳ping pong
        emit pong();
    }
}
//把传入的 QJsonObject，转成 WebSocket 文本消息发出去
void SignalingClient::sendJson(const QJsonObject &obj)
{
    if (!isConnected())
        return;
    m_socket->sendTextMessage(
        QString::fromUtf8(QJsonDocument(obj).toJson(QJsonDocument::Compact)));//发送文本帧数据体data，默认不换行
}

SignalingClient::Member SignalingClient::parseMember(const QJsonObject &obj)
{
    Member m;
    m.id = obj.value(QLatin1String(Protocol::KeyId)).toString();
    m.name = obj.value(QLatin1String(Protocol::KeyName)).toString();
    m.micOn = obj.value(QLatin1String(Protocol::KeyMic)).toBool();
    m.camOn = obj.value(QLatin1String(Protocol::KeyCam)).toBool();
    m.sharing = obj.value(QLatin1String(Protocol::KeySharing)).toBool();
    m.isHost = obj.value(QLatin1String(Protocol::KeyIsHost)).toBool();
    return m;
}

// 媒体帧二进制信封： [4 字节大端 headerLen][header JSON][payload]（封装，用meta记录发送的二进制字节流的时间戳，帧的类型）
QByteArray SignalingClient::packEnvelope(const QJsonObject &header, const QByteArray &payload)
{
    const QByteArray hdr = QJsonDocument(header).toJson(QJsonDocument::Compact);
    QByteArray out;
    const quint32 n = quint32(hdr.size());//将数字转换为大端字节序（倒着数入大小这个数字）
    out.append(char((n >> 24) & 0xff));//除2的24次幂
    out.append(char((n >> 16) & 0xff));
    out.append(char((n >> 8) & 0xff));
    out.append(char(n & 0xff));
    out.append(hdr);
    out.append(payload);
    return out;
}

bool SignalingClient::unpackEnvelope(const QByteArray &data, QJsonObject &meta,QByteArray &payload)
{
    //跳过前四个字节（前四个字节存的是header这个描述二进制数据信息的大小），根据前四个字节存的大小，从data中把header提取出来
    //剩下的payload就是真实的二进制帧数据
    if (data.size() < 4)
        return false;
    //QByteArray是存储字节流，一个元素一个字节（这里先取出前八个字节，左移）
    const quint32 n = (quint32(uchar(data[0])) << 24) | (quint32(uchar(data[1])) << 16)
                    | (quint32(uchar(data[2])) << 8) | quint32(uchar(data[3]));
    if (n > 65536 || data.size() < 4 + int(n))//业务上 meta 只是存时间戳、帧类型，json 很短
        return false;
    QJsonParseError err{};
    const QJsonDocument doc = QJsonDocument::fromJson(data.mid(4, int(n)), &err);
    if (err.error != QJsonParseError::NoError || !doc.isObject())
        return false;
    meta = doc.object();
    payload = data.mid(4 + int(n));
    return true;
}
