#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QToolBar>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QAction>
#include <QLabel>
#include <QDebug>
#include <QFileDialog>
#include <QLineEdit>
#include <QListWidget>

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    void ShowLogin();
    QToolBar *navToolBar;
private:
    void createToolBar();
    void createMainContent();
    void showVideo();  // Added function for showing videos

public slots:
    void ToggleToolBar(bool b);
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
    void ShowLogin();
    void AttemptLogin();
private:

    QMediaPlayer *mediaPlayer;
    QVideoWidget *videoWidget;
    QPushButton *pauseButton;
    QWidget *profileWidget = nullptr;
    QWidget *LoginWidget = nullptr;
};

#endif // MAINWINDOW_H




