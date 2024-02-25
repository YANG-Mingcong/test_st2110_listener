#ifndef STREAMPLAYER_H
#define STREAMPLAYER_H

#include <QObject>

#include <QUdpSocket>
#include <QAudioOutput>
#include <QAudioFormat>
#include <QIODevice>
#include <QAudioSink>

class StreamPlayer : public QObject
{
    Q_OBJECT
public:
    explicit StreamPlayer(QObject *parent = nullptr);
    ~StreamPlayer();

    void startPlaying();  // 启动音频播放

    void setStreamAddr(QHostAddress);
    void setStreamPort(quint16);
    void setStreamAudioDepth(quint16);
    void setStreamAudioFrequency(quint16);
    void setStreamAudioChannels(quint16);


public slots:
    void initializeAudioIO(const QAudioDevice &audioIO);
    void updateAudioIO(const QAudioDevice &audioIO);

private slots:
    void readDatagrams(); // 读取UDP数据的槽函数

private:
    QUdpSocket udpSocket;

    QAudioSink* rawAudio;

    QAudioOutput *audioOutput;
    QIODevice *audioIODevice;

    QHostAddress streamMuilticastAddress;
    quint16 streamMuilticastPort;
    quint16 streamAudioDepth;
    quint16 streamAudioFrequency;
    quint16 streamAudioChannels;

    QScopedPointer<QAudioSink> m_audioOutput;



    void setupAudioOutput(); // 设置音频输出
};

#endif // STREAMPLAYER_H
