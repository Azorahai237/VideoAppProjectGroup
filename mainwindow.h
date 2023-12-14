#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QStackedWidget>
#include <QPushButton>
#include <QVBoxLayout>
#include <QPushButton>
#include <QListWidget>
#include <QLineEdit>
#include <QLabel>
#include <QCamera>
#include <QCameraViewfinder>
#include <QCameraImageCapture>
#include <QStackedLayout>
#include <QMediaRecorder>
#include <QPainter>
#include <QMediaPlayer>
#include <QVideoWidget>
#include <QMediaPlaylist>
#include <QSlider>
#include <QCheckBox>
#include <QtAwesome/QtAwesome.h>
#include <QGraphicsScene>
#include <QGraphicsVideoItem>
#include <QGraphicsTextItem>
#include <QGraphicsView>
#include <QFile>

class MainWindow : public QWidget {
    Q_OBJECT

public:
    MainWindow();

private slots:
    void goToPreviousPage();
    void goToNextPage();
    void goToPage(int index);
    void SetupFeedPage(QWidget *page);
    void SetupAddVideoPage(QWidget *page);
    void SetupProfilePage(QWidget *page);
    void SetupGalleryPage(QWidget *page);
    void SetupLoginPage(QWidget *page);
    void SetupSettingsPage(QWidget *page);
    QCheckBox* addSettingSwitch(QVBoxLayout *layout, const QString &settingName);
    void change_theme();
    void login();
    void logout();
    void updateVolume(int volume);
    void goToPreviousVideo();
    void goToNextVideo();
    void setPosition(int position);

private:
    fa::QtAwesome* awesome;
    bool isLightTheme = true;
    QStackedWidget stackedWidget;
    QPushButton buttonPrevious;
    QPushButton buttonNext;
    QPushButton* buttonPage1;
    QPushButton* buttonPage2;
    QPushButton* buttonPage3;
    QPushButton* buttonPage4;
    QPushButton* buttonPage5;
    QPushButton* buttonPage6;
    QMediaPlayer mediaPlayer;
    QVideoWidget videoWidget;
    QSlider volumeSlider;
    QPushButton* buttonSkipPrevious;
    QPushButton* buttonSkipNext;
    QSlider positionSlider;
    QGraphicsView *graphicsView;
};

#endif // MAINWINDOW_H




