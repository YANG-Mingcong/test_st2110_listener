#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QMediaDevices>

#include "streamplayer.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();



signals:
    void initStreamPlayerAudioIO(QAudioDevice);
    void updateStreamPlayerAudioIO(QAudioDevice);

private:
    Ui::MainWindow *ui;

    StreamPlayer *streamPlayer;

    QMediaDevices *m_devices = nullptr;

    void initializeAudio(const QAudioDevice &deviceInfo);

private slots:

    void deviceChanged(int index);

    void updateAudioDevices();


};


#endif // MAINWINDOW_H
