#include "mainwindow.h"





MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
    createToolBar();
    createMainContent();

    setWindowTitle("Social Media App");

    //setFixedSize(1280, 720);
    setMinimumSize(480, 800); // Smallest standard mobile resolution
    
    mediaPlayer = new QMediaPlayer(this);
    videoWidget = new QVideoWidget(this);
    mediaPlayer->setVideoOutput(videoWidget);

    createMediaPlayerControls();


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
void MainWindow::ToggleToolBar(bool b) {
    if (navToolBar) {
        navToolBar->setVisible(b);
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
    // Create a list widget for displaying videos in the feed
    QListWidget *feedListWidget = new QListWidget(this);
    setCentralWidget(feedListWidget);

    // Simulate video data (replace this with your actual data)
    QStringList videoTitles = {"Video 1", "Video 2", "Video 3"};
    QStringList sharers = {"UserA", "UserB", "UserC"};

    // Populate the feed list with videos and sharers
    for (int i = 0; i < videoTitles.size(); ++i) {

    // Create a list item
    QListWidgetItem *item = new QListWidgetItem(feedListWidget);
    item->setSizeHint(QSize(250, 150));  // Set the size of each item

     // Create a custom widget for the list item
     QWidget *videoItemWidget = new QWidget(feedListWidget);
     videoItemWidget->setStyleSheet("background-color: #f5f5f5; border: 1px solid #ccc; border-radius: 8px; margin: 5px;");

     // Create a layout for the widget
     QVBoxLayout *itemLayout = new QVBoxLayout(videoItemWidget);

     // Add video thumbnail (replace "path_to_thumbnail" with the actual path or URL)
     QLabel *thumbnailLabel = new QLabel(videoItemWidget);
    thumbnailLabel->setPixmap(QPixmap("path_to_thumbnail").scaled(150, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation));
    thumbnailLabel->setAlignment(Qt::AlignCenter);
    itemLayout->addWidget(thumbnailLabel);

    // Add video title label
    QLabel *titleLabel = new QLabel(videoTitles.at(i), videoItemWidget);
    titleLabel->setAlignment(Qt::AlignCenter);
    titleLabel->setStyleSheet("font-weight: bold; margin-top: 5px;");
    itemLayout->addWidget(titleLabel);

    // Add sharer label
    QLabel *sharerLabel = new QLabel("Shared by: " + sharers.at(i), videoItemWidget);
    sharerLabel->setAlignment(Qt::AlignCenter);
    sharerLabel->setStyleSheet("font-style: italic; color: #888;");
    itemLayout->addWidget(sharerLabel);

    // Set the widget for the list item
    feedListWidget->setItemWidget(item, videoItemWidget);

        }

        // Connect the list item click event to a slot (you can implement this slot)
        connect(feedListWidget, &QListWidget::itemClicked, this, [this](){ Q_UNUSED(this); });

    qDebug("Showing Feed section");


}
void MainWindow::AttemptLogin(){
    ToggleToolBar(true);





}

void MainWindow::ShowLogin(){
        QLabel *titleLabel = new QLabel("Login Page", this);
        QLineEdit *usernameLineEdit = new QLineEdit(this);
        QLineEdit *passwordLineEdit = new QLineEdit(this);
        QPushButton *loginButton = new QPushButton("Login", this);
        titleLabel->setAlignment(Qt::AlignCenter);
        usernameLineEdit->setPlaceholderText("Username");
        passwordLineEdit->setPlaceholderText("Password");
        connect(loginButton, &QPushButton::clicked, this, &MainWindow::AttemptLogin);

        QWidget *LoginWidget = new QWidget(this);
        QVBoxLayout *layout = new QVBoxLayout(LoginWidget);
        layout->addWidget(titleLabel);
        layout->addWidget(usernameLineEdit);
        layout->addWidget(passwordLineEdit);
        layout->addWidget(loginButton);

        navToolBar->setVisible(true);
        this->setCentralWidget(LoginWidget);


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


void MainWindow::createMediaPlayerControls() {
    // Create controls for the media player
    QPushButton *playButton = new QPushButton("Play");
    QPushButton *pauseButton = new QPushButton("Pause");
    QSlider *volumeSlider = new QSlider(Qt::Horizontal);
    volumeSlider->setRange(0, 100);
    volumeSlider->setValue(50);

    // Connect buttons to slots
    connect(playButton, &QPushButton::clicked, this, &MainWindow::playVideo);
    connect(pauseButton, &QPushButton::clicked, this, &MainWindow::pauseVideo);
    connect(volumeSlider, &QSlider::valueChanged, this, &MainWindow::setVolume);

    // Layout for media player controls
    QHBoxLayout *mediaPlayerControlsLayout = new QHBoxLayout();
    mediaPlayerControlsLayout->addWidget(playButton);
    mediaPlayerControlsLayout->addWidget(pauseButton);
    mediaPlayerControlsLayout->addWidget(volumeSlider);

    // Add video widget and controls to the central layout
    QVBoxLayout *centralLayout = dynamic_cast<QVBoxLayout*>(centralWidget()->layout());
    if (centralLayout) {
        centralLayout->addWidget(videoWidget);
        centralLayout->addLayout(mediaPlayerControlsLayout);
    }
}

void MainWindow::playVideo() {
    mediaPlayer->play();
}

void MainWindow::pauseVideo() {
    mediaPlayer->pause();
}

void MainWindow::setVolume(int volume) {
    mediaPlayer->setVolume(volume);
}



void MainWindow::showOwnVideos() {
    // Implement the logic to show the "View Own Videos" section
    qDebug("Showing View Own Videos section");
    QString FileName = QFileDialog::getOpenFileName(this,tr("Select Video File"),"",tr("MP4 Files (*.mp4);;All Files (*)"));

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

