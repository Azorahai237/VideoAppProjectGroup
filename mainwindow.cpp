#include "mainwindow.h"





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
void MainWindow::showVideo() {

//     // Set the media content to the provided video file path
//     mediaPlayer->setMedia(QUrl::fromLocalFile("videos/c.mp4"));

//     // Play the video
//     mediaPlayer->play();
}


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

    // Connect the list item click event to a slot (unimplemented)
    connect(feedListWidget, &QListWidget::itemClicked, this, [this](){ Q_UNUSED(this); });

    qDebug("Showing Feed section");

}

void MainWindow::AttemptLogin(){
    qDebug("Processing Login");


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

    // 1st Layer: Top left - Button to go to settings
    QPushButton *settingsButton = new QPushButton("Settings", this);
    connect(settingsButton, &QPushButton::clicked, [this](){ Q_UNUSED(this); });

    // 1st Layer: Top center - Large text "Profile"
    QLabel *profileLabel = new QLabel("Your Profile", this);
    profileLabel->setStyleSheet("font-size: 16pt;");
    profileLabel->setAlignment(Qt::AlignCenter);

    // 1st Layer: Top right - Button to log out
    QPushButton *logoutButton = new QPushButton("Logout", this);
    connect(logoutButton, &QPushButton::clicked, [this](){ Q_UNUSED(this); });

    // Create a horizontal layout for the 1st layer
    QHBoxLayout *layer1Layout = new QHBoxLayout();
    layer1Layout->addWidget(settingsButton);
    layer1Layout->addWidget(profileLabel);
    layer1Layout->addWidget(logoutButton);

    // 2nd Layer: Rounded space for profile image
    QLabel *profileImageLabel = new QLabel(this);
    profileImageLabel->setStyleSheet("border-radius: 50%; border: 2px solid #a0a0a0;");
    profileImageLabel->setFixedSize(150, 150);
    //profileImageLabel->setPixmap(QPixmap("/home/csunix/sc22mt/Pictures/bombadil.jpg"));

    // Create a vertical layout for the 2nd layer
    QHBoxLayout *layer2Layout = new QHBoxLayout();
    layer2Layout->addWidget(profileImageLabel, 0, Qt::AlignHCenter);

    // 3rd Layer: Username
    QLabel *usernameLabel = new QLabel("Username", this);
    usernameLabel->setAlignment(Qt::AlignCenter);
    usernameLabel->setStyleSheet("font-size: 28pt;");

    // Create a vertical layout for the 3rd layer
    QVBoxLayout *layer3Layout = new QVBoxLayout();
    layer3Layout->addWidget(usernameLabel);

    // 4th Layer: Center - User description
    QLabel *descriptionLabel = new QLabel("User Description", this);
    descriptionLabel->setAlignment(Qt::AlignCenter);

    // Create a vertical layout for the 4th layer
    QVBoxLayout *layer4Layout = new QVBoxLayout();
    layer4Layout->addWidget(descriptionLabel);

    // 5th Layer: Custom widget for each post
    class PostWidget : public QWidget {
    public:
        PostWidget(const QString& postText, const QString& profileImagePath, const QString& posterName, QWidget* parent = nullptr) : QWidget(parent) {

            QLabel* profileImageLabel = new QLabel(this);
            profileImageLabel->setFixedSize(50, 50);
            profileImageLabel->setPixmap(QPixmap(profileImagePath));
            profileImageLabel->setStyleSheet("border-radius: 50%; border: 2px solid #a0a0a0;");

            QLabel* nameLabel = new QLabel(posterName, this);
            nameLabel->setStyleSheet("font-weight: bold;");

            QLabel* postTextLabel = new QLabel(postText, this);
            postTextLabel->setWordWrap(true);

            QHBoxLayout* postLayout = new QHBoxLayout(this);
            postLayout->addWidget(profileImageLabel);
            postLayout->addSpacing(10);
            QVBoxLayout* textLayout = new QVBoxLayout();
            textLayout->addWidget(nameLabel, 0, Qt::AlignLeft);
            textLayout->addWidget(postTextLabel);
            postLayout->addLayout(textLayout);

            postLayout->setSpacing(10);
            postLayout->setContentsMargins(10, 10, 10, 10);
        }
    };

    // 5th Layer: - Create 3 PostWidgets,
    PostWidget* post1Widget = new PostWidget("Lorem ipsum dolor sit amet, consectetur adipiscing elit. Maecenas... ", "/home/csunix/sc22mt/Pictures/bombadil.jpg", "Title 1", this);
    PostWidget* post2Widget = new PostWidget("Lorem ipsum dolor sit amet, consectetur adipiscing elit. Maecenas... Lorem ipsum dolor sit amet, consectetur adipiscing elit. Maecenas...", "/home/csunix/sc22mt/Pictures/bombadil.jpg", "Title 2", this);
    PostWidget* post3Widget = new PostWidget("Lorem ipsum dolor sit amet, consectetur adipiscing elit. Maecenas... Lorem ipsum dolor sit amet, consectetur adipiscing elit. Maecenas... Lorem ipsum dolor sit amet, consectetur adipiscing elit. Maecenas...", "/home/csunix/sc22mt/Pictures/bombadil.jpg", "Title 3", this);

    // Create a vertical layout for the 5th layer
    QVBoxLayout* layer5Layout = new QVBoxLayout();
    layer5Layout->addWidget(post1Widget);
    layer5Layout->addWidget(post2Widget);
    layer5Layout->addWidget(post3Widget);

    // Set spacing for the 5th layer
    layer5Layout->setSpacing(10);

    // Create the profile widget
    profileWidget = new QWidget(this);

    // Set the layout for the profile widget as a vertical layout
    QVBoxLayout *profileLayout = new QVBoxLayout(profileWidget);
    profileLayout->addLayout(layer1Layout);
    profileLayout->addStretch(1);
    profileLayout->addLayout(layer2Layout);
    profileLayout->addLayout(layer3Layout);
    profileLayout->addLayout(layer4Layout);
    profileLayout->addStretch(2);
    profileLayout->addLayout(layer5Layout);
    layer5Layout->setAlignment(Qt::AlignHCenter);


    // Ensure the navigation toolbar is visible at the bottom
    navToolBar->setVisible(true);

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

