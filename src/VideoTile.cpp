#include "VideoTile.h"
#include "IconFactory.h"

#include <QFontMetrics>
#include <QLinearGradient>
#include <QMouseEvent>
#include <QPainter>
#include <QPainterPath>

VideoTile::VideoTile(const QString &name, const QColor &avatarColor, bool isSelf,
                     int index, QWidget *parent)
    : QWidget(parent)
    , m_name(name)
    , m_avatarColor(avatarColor)
    , m_isSelf(isSelf)
    , m_index(index)
{
    setMouseTracking(true);
    setCursor(Qt::PointingHandCursor);
    setMinimumSize(80, 60);
}

//以下只要设定打开，就会自动update()
void VideoTile::setMicOn(bool on)
{
    if (m_micOn == on)
        return;
    m_micOn = on;
    update();
}

void VideoTile::setCamOn(bool on)
{
    if (m_camOn == on)
        return;
    m_camOn = on;
    update();
}

void VideoTile::setSpeaking(bool speaking)
{
    if (m_speaking == speaking)
        return;
    m_speaking = speaking;
    update();
}

void VideoTile::setHighlighted(bool highlighted)
{
    if (m_highlighted == highlighted)
        return;
    m_highlighted = highlighted;
    update();
}

void VideoTile::setOccupied(bool occupied)
{
    if (m_occupied == occupied)
        return;
    m_occupied = occupied;
    update();
}

void VideoTile::setSharing(bool sharing)
{
    if (m_sharing == sharing)
        return;
    m_sharing = sharing;
    update();
}

void VideoTile::setFillMode(FillMode mode)
{
    if (m_fillMode == mode)
        return;
    m_fillMode = mode;
    update();
}

void VideoTile::setVideoFrame(const QImage &frame)
{
    m_videoImage = frame;
    m_hasVideo = true;//表示接受到新的有效数据帧，之后paintEvent会用到
    update();
}

void VideoTile::clearVideoFrame()
{
    m_videoImage = QImage();
    m_hasVideo = false;
    update();
}

void VideoTile::enterEvent(QEnterEvent *event)
{
    Q_UNUSED(event);
    m_hover = true;
    update();
}

void VideoTile::leaveEvent(QEvent *event)
{
    Q_UNUSED(event);
    m_hover = false;
    update();
}

void VideoTile::mousePressEvent(QMouseEvent *event)//点击控件触发信号，对应槽函数会取消前一个瓦片窗口的边框高亮，设置当前窗口边框高亮
{
    Q_UNUSED(event);
    emit clicked(m_index);
}

//渲染瓦片宫格窗口的右下角麦克风和摄像头图标
void VideoTile::drawStatusIcons(QPainter &p, const QRectF &r) const
{
    const qreal icon = 15;
    const qreal gap  = 5;
    const qreal y    = r.bottom() - icon - 8;
    const qreal xCam = r.right() - icon - 8;
    const qreal xMic = xCam - icon - gap;

    const QColor iconColor(255, 255, 255, 200);
    IconFactory::drawIcon(p, QRectF(xCam, y, icon, icon), IconFactory::IconKind::Camera, iconColor, !m_camOn);
    IconFactory::drawIcon(p, QRectF(xMic, y, icon, icon), IconFactory::IconKind::Mic, iconColor, !m_micOn);
}
//渲染当前帧的画面
void VideoTile::drawVideo(QPainter &p, const QRectF &r)
{
    if (m_videoImage.isNull())
        return;
    //先按比例绘制一个画布，将Image画到画布上（画布的缩放就是图片的缩放），达到按比例缩放图片的目的
    const qreal scale = (m_fillMode == FillMode::Crop)//缩放倍数（Crop裁剪就应该取最大）
                            ? qMax(r.width() / m_videoImage.width(), r.height() / m_videoImage.height())
                            : qMin(r.width() / m_videoImage.width(), r.height() / m_videoImage.height());
    const int w = qRound(m_videoImage.width() * scale);//按比例缩放，去除浮点数精度
    const int h = qRound(m_videoImage.height() * scale);
    const QRect target(int(r.center().x()) - w / 2, int(r.center().y()) - h / 2, w, h);//随中心而动，得到瓦片窗口的矩形

    // 圆角裁剪：先裁剪到圆角路径，再绘制视频
    QPainterPath clip;
    clip.addRoundedRect(r, 12, 12);//配置遮罩板
    p.save();
    p.setClipPath(clip);//设置遮罩板
    p.drawImage(target, m_videoImage);
    p.restore();
}
//在没有渲染出直播画面时，先渲染出头像
void VideoTile::drawAvatar(QPainter &p, const QRectF &r)
{
    const qreal cx = r.center().x();
    const qreal cy = r.center().y();
    const qreal av = qMin(r.width(), r.height()) * 0.42;
    QRectF avRect(cx - av / 2, cy - av / 2, av, av);

    p.setPen(Qt::NoPen);
    p.setBrush(QColor(0, 0, 0, 45));
    p.drawEllipse(avRect.translated(0, 2));
    p.setBrush(QColor(255, 255, 255, 235));
    p.drawEllipse(avRect);

    QFont f = p.font();
    f.setPointSizeF(av * 0.36);
    f.setBold(true);
    p.setFont(f);
    p.setPen(m_avatarColor.darker(120));
    p.drawText(avRect, Qt::AlignCenter, m_name.left(1));//居中显示文本
}
//关闭摄像头后出现的人像与“摄像头已关闭”图样渲染
void VideoTile::drawSilhouette(QPainter &p, const QRectF &r)
{
    const qreal cx = r.center().x();
    const qreal cy = r.center().y();
    const qreal hs = qMin(r.width(), r.height()) * 0.26;

    p.setPen(Qt::NoPen);
    p.setBrush(QColor(255, 255, 255, 45));
    p.drawEllipse(QPointF(cx, cy - hs * 0.35), hs * 0.52, hs * 0.52);

    QPainterPath body;
    body.moveTo(cx - hs * 0.85, cy + hs * 0.95);
    body.quadTo(cx - hs * 0.85, cy + hs * 0.2, cx, cy + hs * 0.2);
    body.quadTo(cx + hs * 0.85, cy + hs * 0.2, cx + hs * 0.85, cy + hs * 0.95);
    body.closeSubpath();
    p.drawPath(body);

    QFont f = p.font();
    f.setPointSizeF(qMax(8.0, r.height() * 0.05));
    p.setFont(f);
    p.setPen(QColor(255, 255, 255, 150));
    p.drawText(QRectF(0, cy + hs * 1.05, width(), height() * 0.1), Qt::AlignHCenter,
               QStringLiteral("摄像头已关闭"));
}

void VideoTile::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter p(this);
    p.setRenderHint(QPainter::Antialiasing);
//给控件设定边框
    const QRectF r = QRectF(rect()).adjusted(1, 1, -1, -1);//因为之前的GridContainer已经设定了控件的大小和位置，Rect类坐标默认以控件为基准而不是整个屏幕

    // 空位占位：虚线框 + "等待加入"
    if (!m_occupied) {
        p.setPen(QPen(QColor(0xff, 0xff, 0xff, 70), 1.5, Qt::DashLine));
        p.setBrush(QColor(0xff, 0xff, 0xff, 12));//极淡白色透明
        p.drawRoundedRect(r, 12, 12);
        QFont f = p.font();
        f.setPointSizeF(qMax(8.0, r.height() * 0.055));
        p.setFont(f);
        p.setPen(QColor(0xff, 0xff, 0xff, 130));
        p.drawText(r, Qt::AlignCenter, QStringLiteral("等待成员加入"));
        return;
    }

    // 瓦片背景渐变（跟模拟视频源背景不一样，只有在开启摄像头过渡时才能看到这个背景）
    QLinearGradient grad(r.topLeft(), r.bottomRight());
    if (m_camOn) {
        grad.setColorAt(0.0, m_avatarColor.lighter(140));
        grad.setColorAt(1.0, m_avatarColor.darker(140));
    } else {
        grad.setColorAt(0.0, QColor(0x33, 0x38, 0x40));
        grad.setColorAt(1.0, QColor(0x1f, 0x23, 0x29));
    }
    p.setPen(Qt::NoPen);
    p.setBrush(grad);
    p.drawRoundedRect(r, 12, 12);

    // 中央内容：摄像头关闭 -> 剪影；开启且有画面 -> 视频；否则 -> 头像（等待画面）
    if (!m_camOn) {
        drawSilhouette(p, r);//摄像头关闭
    } else if (m_hasVideo) {
        drawVideo(p, r);//摄像头打开，接收到有效的数据帧
    } else {//摄像头打开，但没有接收到有效数据帧
        drawAvatar(p, r);
        // 提示"摄像头启动中"
        QFont f = p.font();
        f.setPointSizeF(qMax(8.0, r.height() * 0.045));
        p.setFont(f);
        p.setPen(QColor(255, 255, 255, 120));
        p.drawText(QRectF(0, r.center().y() + r.height() * 0.30, width(), height() * 0.1),
                   Qt::AlignHCenter, QStringLiteral("摄像头启动中..."));
    }

    // 名字胶囊（左下）
    QFont nf = p.font();
    nf.setPointSizeF(qMax(8.5, r.height() * 0.055));
    p.setFont(nf);
    const QString shown = m_isSelf ? m_name + QStringLiteral("（我）") : m_name;
    const QFontMetrics fm(nf);
    const int textW = fm.horizontalAdvance(shown);
    const int pillH = qMax(18, int(r.height() * 0.13));
    const int pad   = 9;
    QRectF pill(r.left() + 8, r.bottom() - pillH - 8, textW + pad * 2, pillH);
    p.setPen(Qt::NoPen);
    p.setBrush(m_isSelf ? QColor(0x2e, 0x8b, 0xff, 200) : QColor(0, 0, 0, 110));
    p.drawRoundedRect(pill, pillH / 2, pillH / 2);
    p.setPen(Qt::white);
    p.drawText(pill.adjusted(pad, 0, -pad, 0), Qt::AlignLeft | Qt::AlignVCenter, shown);

    // 状态图标（右下）
    drawStatusIcons(p, r);

    // 共享中角标（左上）
    if (m_sharing) {
        QFont sf = p.font();
        sf.setPointSizeF(qMax(7.5, r.height() * 0.05));
        p.setFont(sf);
        const QString label = QStringLiteral("共享中");
        const QFontMetrics sfm(sf);
        const int sh = qMax(16, int(r.height() * 0.11));
        const int sw = sfm.horizontalAdvance(label) + 9 + 10 + 8; // 图标+文字+内边距
        const QRectF badge(r.left() + 8, r.top() + 8, sw, sh);
        p.setPen(Qt::NoPen);
        p.setBrush(QColor(0x2e, 0x8b, 0xff, 215));
        p.drawRoundedRect(badge, sh / 2, sh / 2);
        const qreal ic = sh * 0.6;
        IconFactory::drawIcon(p, QRectF(badge.left() + 6, badge.top() + (sh - ic) / 2, ic, ic),
                              IconFactory::IconKind::Share, Qt::white);
        p.setPen(Qt::white);
        p.drawText(QRectF(badge.left() + 6 + ic + 3, badge.top(), sw - 6 - ic - 3, sh),
                   Qt::AlignLeft | Qt::AlignVCenter, label);
    }

    // 说话 / 选中边框
    if (m_speaking) {
        p.setPen(QPen(QColor(0x2e, 0xc4, 0x6b), 2.5));
        p.setBrush(Qt::NoBrush);
        p.drawRoundedRect(r.adjusted(0.5, 0.5, -0.5, -0.5), 12, 12);
    } else if (m_highlighted) {
        p.setPen(QPen(QColor(0x4a, 0x9e, 0xff), 2.0));
        p.setBrush(Qt::NoBrush);
        p.drawRoundedRect(r.adjusted(0.5, 0.5, -0.5, -0.5), 12, 12);
    } else if (m_hover) {
        p.setPen(QPen(QColor(255, 255, 255, 110), 1.5));
        p.setBrush(Qt::NoBrush);
        p.drawRoundedRect(r.adjusted(0.5, 0.5, -0.5, -0.5), 12, 12);
    }
}
