#include "AudioSource.h"

#include <QAudio>
#include <QAudioSource>
#include <QDebug>
#include <QIODevice>
#include <QMediaDevices>
#include <QtMath>

namespace {

// 读取 PCM(Int16) 缓冲并计算归一化 RMS（0.0 ~ 1.0，1.0 = 满幅）
    //测量一小段时间内的声音所有瞬时响度平方，加和，开方，求平均，算百分比。得出这一段时间平均能量大小，
    // 也就是音量的大小（给人看音量；给机器看用来识别是否有声音，需不需要发包）
float computeRms(const QByteArray &data)
{
    if (data.size() < 2)
        return 0.0f;
    const qint16 *samples = reinterpret_cast<const qint16 *>(data.constData());
    const int count = data.size() / 2;
    qint64 sum = 0;
    for (int i = 0; i < count; ++i) {
        const qint32 s = samples[i];
        sum += qint64(s) * s;
    }
    return static_cast<float>(qSqrt(qreal(sum) / count) / 32768.0);
}

} // namespace

AudioLevelSource::AudioLevelSource(QObject *parent)
    : QObject(parent)
    , m_deviceInfo(QMediaDevices::defaultAudioInput())
{
    // 44.1kHz 单声道 Int16：通用格式，绝大多数设备直接支持
    m_format.setSampleRate(44100);
    m_format.setChannelCount(1);
    m_format.setSampleFormat(QAudioFormat::Int16);//每一个音频采样占用 2 字节，有符号整数，对应computeRms中reinterpret_cast<const qint16 *>操作
}

AudioLevelSource::~AudioLevelSource()
{
    stop();
}

void AudioLevelSource::start()
{
    if (m_source)
        return;

    if (m_deviceInfo.isNull()) {
        emit errorOccurred(QStringLiteral("未检测到音频输入设备"));
        return;
    }
    if (!m_format.isValid()) {
        emit errorOccurred(QStringLiteral("音频格式无效"));
        return;
    }

    m_source = new QAudioSource(m_deviceInfo, m_format, this);
    m_device = m_source->start();
    if (!m_device) {
        emit errorOccurred(QStringLiteral("无法打开音频输入，请检查麦克风权限"));
        delete m_source;
        m_source = nullptr;
        return;
    }

    connect(m_device, &QIODevice::readyRead, this, &AudioLevelSource::onReadyRead);
    connect(m_source, &QAudioSource::stateChanged, this, [this](QAudio::State state) {
        // 运行中突然进入 StoppedState 视为设备错误（权限被撤 / 设备被拔）
        if (state == QAudio::StoppedState && m_source
            && m_source->error() != QAudio::NoError)
        {//麦克风驱动状态停止，但是麦克风驱动已经部署，，驱动报错
            emit errorOccurred(QStringLiteral("音频输入出错，已停止采集"));
            stop();
        }
    });
}

void AudioLevelSource::stop()
{
    if (m_source) {
        m_source->stop();
        m_source->deleteLater();
        m_source = nullptr;
    }
    m_device = nullptr;
    updateState(false);
    m_smoothed = 0.0f;
    m_silentRuns = 0;
}

void AudioLevelSource::setDevice(const QAudioDevice &device)
{
    if (device == m_deviceInfo)
        return;
    const bool running = (m_source != nullptr);
    stop();
    m_deviceInfo = device;
    if (running)
        start();
}
//当麦克风硬件数据传来触发这个槽函数，槽函数判断音量
void AudioLevelSource::onReadyRead()
{
    if (!m_device)
        return;
    const QByteArray data = m_device->readAll();
    const float level = computeRms(data);//计算真实音量大小

    // 平滑：短暂尖峰不会误触发，持续音量才判定
    m_smoothed = m_smoothed * 0.7f + level * 0.3f;

    // 滞回阈值：开始说话要求更高，持续说话用更低阈值保持，避免边界抖动
    constexpr float kSpeakStart = 0.018f;
    constexpr float kSpeakHold  = 0.010f;
    if (m_speaking) {
        if (m_smoothed < kSpeakHold) {
            if (++m_silentRuns >= 8) // 连续静音才判定停止说话
                updateState(false);
        } else {
            m_silentRuns = 0;
        }
    } else if (m_smoothed > kSpeakStart) {
        m_silentRuns = 0;
        updateState(true);
    }

    emit levelChanged(m_smoothed);//发一个当前音量水平的信号，携带当前音量的大小，在录音或通话界面，用这个信号的值来驱动一个动态变化的音量条，让用户直观地看到自己声音的大小。
    emit audioData(data);//传输最原始的音频数据（PCM 数据）的信号，讲一次采集到的数据发出去
}

void AudioLevelSource::updateState(bool speaking)
{
    if (m_speaking == speaking)
        return;
    m_speaking = speaking;
    emit speakingChanged(speaking);//布尔状态开关，检测有人是否在说话的信号
}
