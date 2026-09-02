#pragma once

#include <QColor>
#include <QImage>
#include <QString>
#include <QWidget>

class QPaintEvent;
class QMouseEvent;

// 单个视频宫格控件：模拟一个会议成员的画面。
// 包含：视频帧/背景渐变 + 头像（首字）+ 名字胶囊 + 麦克风/摄像头状态图标。
// 支持：视频渲染（裁剪填充/等比缩放）、说话高亮、选中高亮、摄像头关闭（剪影）、空位占位。
class VideoTile : public QWidget
{
    Q_OBJECT
public:
    // 视频填充方式
    enum class FillMode {
        Crop, // 裁剪填充：视频铺满宫格，超出部分裁掉（默认，观感最佳）
        Fit   // 等比缩放：完整显示视频，四周留边
    };

    explicit VideoTile(const QString &name, const QColor &avatarColor, bool isSelf,
                       int index, QWidget *parent = nullptr);

    QString name() const { return m_name; }
    int     index() const { return m_index; }
    bool    isSelf() const { return m_isSelf; }

    void setMicOn(bool on);
    void setCamOn(bool on);
    void setSpeaking(bool speaking);
    void setHighlighted(bool highlighted);
    void setOccupied(bool occupied); // false 表示空格子占位
    void setSharing(bool sharing);   // 共享屏幕状态（左上角显示"共享中"角标）

    // 视频画面
    void setFillMode(FillMode mode);
    FillMode fillMode() const { return m_fillMode; }
    void setVideoFrame(const QImage &frame);
    void clearVideoFrame();
    bool hasVideoFrame() const { return m_hasVideo; }

    bool micOn() const { return m_micOn; }
    bool camOn() const { return m_camOn; }

signals:
    void clicked(int index);

protected:
    void paintEvent(QPaintEvent *event) override;
    void mousePressEvent(QMouseEvent *event) override;
    void enterEvent(QEnterEvent *event) override;
    void leaveEvent(QEvent *event) override;

private:
    void drawStatusIcons(QPainter &p, const QRectF &r) const;
    void drawVideo(QPainter &p, const QRectF &r);
    void drawSilhouette(QPainter &p, const QRectF &r);
    void drawAvatar(QPainter &p, const QRectF &r);

    QString  m_name;//成员昵称
    QColor   m_avatarColor;//头像背景色
    bool     m_isSelf      = false;//是否是自己（本机主持人）
    int      m_index       = 0;//瓦片下标，对应m_members`数组下标
    bool     m_micOn       = true;//麦克风开关
    bool     m_camOn       = true;//摄像头开关
    bool     m_speaking    = false;//是否正在说话（绿色高亮边框）
    bool     m_highlighted = false;//被选中（蓝色高亮边框）
    bool     m_occupied    = true;//是否是有效成员；false = 空位 “等待成员加入”
    bool     m_sharing     = false;//是否屏幕共享，左上角显示 “共享中” 标签
    bool     m_hover       = false;//鼠标悬浮状态

    // 视频
    FillMode m_fillMode = FillMode::Crop;//画面填充模式
    QImage   m_videoImage;//保存一帧 QImage 视频画面
    bool     m_hasVideo = false;//是否已经收到有效视频帧
};
