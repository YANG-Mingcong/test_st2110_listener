#include "streamplayer.h"

#include <QDateTime>


StreamPlayer::StreamPlayer(QObject *parent)
    : QObject{parent}
{

    //init data for local test
    this->setStreamAddr(QHostAddress("239.69.12.33"));
    this->setStreamPort(5004);
    this->setStreamAudioFrequency(48000);
    this->setStreamAudioDepth(24);
    this->setStreamAudioChannels(1);

    this->setupAudioOutput();

    udpSocket.bind(streamMuilticastAddress, streamMuilticastPort, QUdpSocket::ReuseAddressHint);
    udpSocket.joinMulticastGroup(streamMuilticastAddress);

    // 连接读取数据的槽函数
    connect(&udpSocket, &QUdpSocket::readyRead,
            this, &StreamPlayer::readDatagrams);

}

StreamPlayer::~StreamPlayer()
{
    disconnect(&udpSocket, &QUdpSocket::readyRead,
            this, &StreamPlayer::readDatagrams);

    udpSocket.deleteLater();
}

void StreamPlayer::startPlaying()
{
    // 设置音频输出参数
    QAudioFormat format;
    format.setSampleRate(streamAudioFrequency);
    format.setChannelCount(streamAudioChannels);


    format.setSampleRate(48000);
    format.setChannelCount(2);
    format.setSampleFormat(QAudioFormat::Int32);




}


void StreamPlayer::setStreamAddr(QHostAddress _addr)
{
    streamMuilticastAddress = _addr;
}

void StreamPlayer::setStreamPort(quint16 _port)
{
    streamMuilticastPort = _port;
}

void StreamPlayer::setStreamAudioDepth(quint16 _depth)
{
    streamAudioDepth = _depth;
}

void StreamPlayer::setStreamAudioFrequency(quint16 _freq)
{
    streamAudioFrequency = _freq;
}

void StreamPlayer::setStreamAudioChannels(quint16 _channelsCounts)
{
    streamAudioChannels = _channelsCounts;
}

void StreamPlayer::initializeAudioIO(const QAudioDevice &audioIO)
{
    // 设置音频输出参数 temporary
    QAudioFormat format;
    format.setSampleRate(streamAudioFrequency);
    format.setChannelCount(streamAudioChannels);


    format.setSampleRate(48000);
    format.setChannelCount(2);
    format.setSampleFormat(QAudioFormat::Int32);

    m_audioOutput.reset(new QAudioSink(audioIO, format));
    qDebug() << "Now Using Device" << audioIO.description();
}

void StreamPlayer::updateAudioIO(const QAudioDevice &audioIO)
{
    m_audioOutput->stop();
    m_audioOutput->disconnect(this);
    this->initializeAudioIO(audioIO);
}

void StreamPlayer::readDatagrams()
{
    // 从UDP套接字读取数据
    while (udpSocket.hasPendingDatagrams())
    {
        QByteArray datagram;
        datagram.resize(udpSocket.pendingDatagramSize());
        udpSocket.readDatagram(datagram.data(), datagram.size());

        // 写入音频输出设备
        // audioIODevice->write(datagram);
        // qDebug() << QDateTime::currentDateTime() << "  --  "  << datagram;
    }

}

void StreamPlayer::setupAudioOutput()
{

}
