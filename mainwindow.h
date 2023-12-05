#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QToolBar>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QPushButton>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);

private:
    void createToolBar();
    void createMainContent();
    void showVideo();  // Added function for showing videos


private slots:
    void playVideo();
    void pauseVideo();
    void setVolume(int volume);
    void showAddVideos();
    void showFeed();
    void showProfile();
    void showOwnVideos();
    void showHome();
    // void pauseVideo();  // Added slot for pausing the video
    void handleMediaStateChanged();
    void handleMediaStatusChanged();
    void createMediaPlayerControls();
private:
    QToolBar *navToolBar;
    QMediaPlayer *mediaPlayer;
    QVideoWidget *videoWidget;
    QPushButton *pauseButton = nullptr;
    QWidget *profileWidget = nullptr;
};

#endif // MAINWINDOW_H
