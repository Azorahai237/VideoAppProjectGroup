#include "mainwindow.h"
#include <QAction>
#include <QVBoxLayout>
#include <QLabel>
#include <QDebug>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    createToolBar();
    createMainContent();

    setWindowTitle("Social Media App");
    setFixedSize(720, 1280);
}

void MainWindow::createToolBar() {
    // Create a toolbar and set its appearance
    navToolBar = new QToolBar(this);
    navToolBar->setStyleSheet("QToolBar { border: 1px solid #a0a0a0; background-color: #f0f0f0; }");

    // Create actions for each section with text
    QAction *addVideosAction = new QAction("Add Videos", this);
    QAction *feedAction = new QAction("Feed", this);
    QAction *profileAction = new QAction("Profile", this);
    QAction *viewOwnVideosAction = new QAction("View Own Videos", this);
    QAction *homeAction = new QAction("Home", this);

    // Connect actions to slots (you can implement these slots)
    connect(addVideosAction, &QAction::triggered, this, &MainWindow::showAddVideos);
    connect(feedAction, &QAction::triggered, this, &MainWindow::showFeed);
    connect(profileAction, &QAction::triggered, this, &MainWindow::showProfile);
    connect(viewOwnVideosAction, &QAction::triggered, this, &MainWindow::showOwnVideos);
    connect(homeAction, &QAction::triggered, this, &MainWindow::showHome);

    // Add actions and separators to the toolbar with spacing
    navToolBar->addAction(addVideosAction);
    navToolBar->addSeparator();
    navToolBar->addAction(feedAction);
    navToolBar->addSeparator();
    navToolBar->addAction(profileAction);
    navToolBar->addSeparator();
    navToolBar->addAction(viewOwnVideosAction);
    navToolBar->addSeparator();
    navToolBar->addAction(homeAction);

    // Add toolbar to the bottom of the main window
    addToolBar(Qt::BottomToolBarArea, navToolBar);
}

void MainWindow::pauseVideo() {
    if (mediaPlayer->state() == QMediaPlayer::PlayingState) {
        mediaPlayer->pause();
    } else if (mediaPlayer->state() == QMediaPlayer::PausedState) {
        mediaPlayer->play();
    }
}
// void MainWindow::showVideo() {

//     // Set the media content to the provided video file path
//     mediaPlayer->setMedia(QUrl::fromLocalFile("videos/c.mp4"));

//     // Play the video
//     mediaPlayer->play();
// }


void MainWindow::createMainContent() {
    // Create a central widget with a simple label to represent the main content
    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    QLabel *contentLabel = new QLabel("Main Content Goes Here");
    contentLabel->setAlignment(Qt::AlignCenter);
    layout->addWidget(contentLabel);
}




void MainWindow::handleMediaStateChanged(){
    qDebug("Media change");
}

void MainWindow::handleMediaStatusChanged(){
    qDebug("Media change");
}

void MainWindow::showAddVideos() {
    // Implement the logic to show the "Add Videos" section
    qDebug("Showing Add Videos section");
}

void MainWindow::showFeed() {
    // Implement the logic to show the "Feed" section
    qDebug("Showing Feed section");


}

void MainWindow::showProfile() {
    // Implement the logic to show the "Profile" section
    qDebug("Showing Profile section");
}

void MainWindow::showOwnVideos() {
    // Implement the logic to show the "View Own Videos" section
    qDebug("Showing View Own Videos section");
    QString FileName = QFileDialog::getOpenFileName(this,tr("Select Video File"),"",tr("MP4 Files (*.MP4"));

    QWidget *centralWidget = new QWidget(this);
    setCentralWidget(centralWidget);

    QVBoxLayout *layout = new QVBoxLayout(centralWidget);

    // Create a video widget
    videoWidget = new QVideoWidget(this);
    layout->addWidget(videoWidget);

    // Create a video player
    mediaPlayer = new QMediaPlayer(this);
    mediaPlayer->setVideoOutput(videoWidget);


    mediaPlayer->setMedia(QUrl(FileName));
    mediaPlayer->play();

}

void MainWindow::showHome() {
    // Implement the logic to show the "Home" section
    qDebug("Showing Home section");
}

