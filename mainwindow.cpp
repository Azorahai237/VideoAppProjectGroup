#include "mainwindow.h"
#include <QAction>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QLabel>
#include <QDebug>
#include <QFileDialog>

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    createToolBar();
    createMainContent();

    setWindowTitle("Social Media App");
    //setFixedSize(1280, 720);
    setMinimumSize(480, 800); // Smallest standard mobile resolution

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
    // Check if the profile widget is already created
    if (!profileWidget) {
        // 1st Layer: Top left - Button to go to settings
        QPushButton *settingsButton = new QPushButton("Settings", this);
        // Connect the button to a lambda function that does nothing for testing purposes
        connect(settingsButton, &QPushButton::clicked, [this](){ Q_UNUSED(this); });

        // 1st Layer: Top center - Large text "Profile"
        QLabel *profileLabel = new QLabel("Profile", this);
        profileLabel->setAlignment(Qt::AlignCenter);

        // 1st Layer: Top right - Button to log out
        QPushButton *logoutButton = new QPushButton("Logout", this);
        // Connect the button to a lambda function that does nothing for testing purposes
        connect(logoutButton, &QPushButton::clicked, [this](){ Q_UNUSED(this); });

        // Create a horizontal layout for the 1st layer
        QHBoxLayout *layer1Layout = new QHBoxLayout();

        // Add the 1st layer elements to the layout
        layer1Layout->addWidget(settingsButton);
        layer1Layout->addWidget(profileLabel);
        layer1Layout->addWidget(logoutButton);
        // 2nd Layer: Center - Circular space for profile image
        QHBoxLayout *profileImageLayout = new QHBoxLayout();

        QLabel *profileImageLabel = new QLabel(this);
        // Set a circular border for the profile image
        profileImageLabel->setStyleSheet("border-radius: 50%; border: 2px solid #a0a0a0;");
        // Set the profile image (replace "path_to_profile_image" with the actual path or URL)
        profileImageLabel->setFixedSize(100, 100); // Set the size of the circular space
        profileImageLabel->setPixmap(QPixmap("/home/csunix/sc22mt/Pictures/bombadil.jpg")); // Image doesn't seem to take the border radius settings

        profileImageLayout->addWidget(profileImageLabel); // Added to avoid memory leak issues


        // Add the profile image label to the layout
        //profileImageLayout->addWidget(profileImageLabel, 0, Qt::AlignCenter);


        // 3rd Layer: Center - Username
        QLabel *usernameLabel = new QLabel("Username", this);
        usernameLabel->setAlignment(Qt::AlignCenter);

        // 4th Layer: Center - User description
        QLabel *descriptionLabel = new QLabel("User Description", this);
        descriptionLabel->setAlignment(Qt::AlignCenter);

        // 5th Layer: Center - 3 vertical timestamped text boxes
        // You can customize the content and appearance as needed
        QLabel *post1 = new QLabel("Post 1 - Timestamp", this);
        QLabel *post2 = new QLabel("Post 2 - Timestamp", this);
        QLabel *post3 = new QLabel("Post 3 - Timestamp", this);

        // Create the profile widget
        profileWidget = new QWidget(this);

        // Set the layout for the profile widget as a vertical layout
        QVBoxLayout *profileLayout = new QVBoxLayout(profileWidget);
        profileLayout->addLayout(layer1Layout);  // Add the 1st layer layout
        profileLayout->addWidget(profileImageLabel, 0, Qt::AlignHCenter);
        profileLayout->addWidget(usernameLabel);
        profileLayout->addWidget(descriptionLabel);
        profileLayout->addWidget(post1);
        profileLayout->addWidget(post2);
        profileLayout->addWidget(post3);

        // Ensure the navigation toolbar is visible at the bottom
        navToolBar->setVisible(true);
    }

    // Set the profile widget as the central widget
    setCentralWidget(profileWidget);

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

