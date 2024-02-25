#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    streamPlayer = new StreamPlayer(this);
    streamPlayer->setStreamAddr(QHostAddress(ui->muilticastIPAddrLineEdit->text()));
    streamPlayer->setStreamPort(ui->muilticastPortSpinBox->value());
    streamPlayer->setStreamAudioFrequency(ui->audioSampleRateSpinBox->value());
    streamPlayer->setStreamAudioChannels(ui->audioChannelCountsSpinBox->value());


    const QAudioDevice &defaultDeviceInfo = m_devices->defaultAudioOutput();
    ui->m_deviceBox->addItem(defaultDeviceInfo.description(),
                             QVariant::fromValue(defaultDeviceInfo));

    for (auto &deviceInfo : m_devices->audioOutputs()) {
        if (deviceInfo != defaultDeviceInfo)
            ui->m_deviceBox->addItem(deviceInfo.description(),
                                     QVariant::fromValue(deviceInfo));
    }

    connect(ui->m_deviceBox, QOverload<int>::of(&QComboBox::activated),
            this, &MainWindow::deviceChanged);

    connect(m_devices, &QMediaDevices::audioOutputsChanged,
            this, &MainWindow::updateAudioDevices);

    connect(this, &MainWindow::initStreamPlayerAudioIO,
            streamPlayer, &StreamPlayer::initializeAudioIO);

    connect(this, &MainWindow::updateStreamPlayerAudioIO,
            streamPlayer, &StreamPlayer::updateAudioIO);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::initializeAudio(const QAudioDevice &deviceInfo)
{
    emit this->initStreamPlayerAudioIO(deviceInfo);
    emit this->updateStreamPlayerAudioIO(deviceInfo);
}

void MainWindow::deviceChanged(int index)
{
    initializeAudio(ui->m_deviceBox->itemData(index).value<QAudioDevice>());
}

void MainWindow::updateAudioDevices()
{
    ui->m_deviceBox->clear();
    const QList<QAudioDevice> devices = m_devices->audioOutputs();
    for (const QAudioDevice &deviceInfo : devices)
        ui->m_deviceBox->addItem(deviceInfo.description(), QVariant::fromValue(deviceInfo));
}

