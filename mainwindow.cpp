#include "mainwindow.h"



class RecordButton : public QPushButton {
public:
    RecordButton(QWidget* parent = nullptr) : QPushButton(parent), clickCount(0) {
        setFixedSize(50, 50);  // Set the size as per your requirement
        updateButtonColor();
        connect(this, &QPushButton::clicked, this, &RecordButton::onClicked);
    }

protected:
    void paintEvent(QPaintEvent* event) override {
        QPushButton::paintEvent(event);

        QPainter painter(this);
        painter.setRenderHint(QPainter::Antialiasing, true);

        painter.setBrush(buttonColor);
        painter.drawEllipse(rect().adjusted(5, 5, -5, -5));
    }

private slots:
    void onClicked() {
        clickCount++;
        updateButtonColor();
    }

    void updateButtonColor() {
        buttonColor = (clickCount % 2 == 0) ? Qt::white : Qt::red;
        update();  // Trigger repainting to reflect the new state
    }

private:
    int clickCount;
    QColor buttonColor;
};

MainWindow::MainWindow(){
    awesome = new fa::QtAwesome(this);
    awesome->initFontAwesome();

    // Create six pages
    QWidget *pages[6];

    for (int i = 0; i < 6; ++i) {
        pages[i] = new QWidget;

        // Call the respective setup function for each page
        if (i == 0) {
            SetupFeedPage(pages[i]);
        } else if (i == 1) {
            SetupAddVideoPage(pages[i]);
        } else if (i == 2) {
            SetupGalleryPage(pages[i]);
        } else if (i == 3) {
            SetupProfilePage(pages[i]);
        } else if (i == 4) {
            SetupLoginPage(pages[i]);
        } else if (i == 5) {
            SetupSettingsPage(pages[i]);
         }

        stackedWidget.addWidget(pages[i]);
    }

    // Connect buttons to navigate through pages

    buttonPage1 = new QPushButton(awesome->icon("fa-house"), "Feed");
    buttonPage2 = new QPushButton(awesome->icon("fa-video"), "Add Video");
    buttonPage3 = new QPushButton(awesome->icon("fa-image"), "Gallery");
    buttonPage4 = new QPushButton(awesome->icon("fa-circle-user"), "Profile");
    buttonPage5 = new QPushButton(awesome->icon("fa-right-to-bracket"), "Login");

    buttonPage4->setVisible(false);

    connect(buttonPage1, &QPushButton::clicked, this, [this](){ goToPage(0); });
    connect(buttonPage2, &QPushButton::clicked, this, [this](){ goToPage(1); });
    connect(buttonPage3, &QPushButton::clicked, this, [this](){ goToPage(2); });
    connect(buttonPage4, &QPushButton::clicked, this, [this](){ goToPage(3); });
    connect(buttonPage5, &QPushButton::clicked, this, [this](){ goToPage(4); });
    // connect(&buttonPage5, &QPushButton::clicked, this, [this](){ goToPage(4); });
    // connect(&buttonPage6, &QPushButton::clicked, this, [this](){ goToPage(5); });

    // Create a layout for the main window
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(&stackedWidget);

    QHBoxLayout *buttonLayout = new QHBoxLayout;

    buttonLayout->addWidget(buttonPage1);
    buttonLayout->addWidget(buttonPage2);
    buttonLayout->addWidget(buttonPage3);
    buttonLayout->addWidget(buttonPage4);
    buttonLayout->addWidget(buttonPage5);
    // mainLayout->addWidget(&buttonPage5);
    // mainLayout->addWidget(&buttonPage6);
    mainLayout->addLayout(buttonLayout);
    setLayout(mainLayout);
}



void MainWindow::SetupFeedPage(QWidget *page) {
    QVBoxLayout *layout = new QVBoxLayout(page);

    // Simulate video data (replace this with your actual data)
    QStringList videoTitles = {"Video 1", "Video 2", "Video 3", "Video 4", "Video 5", "Video 6"};
    QStringList sharers = {"UserA", "UserB", "UserC", "UserD", "UserE", "UserF"};

    QListWidget *feedListWidget = new QListWidget;

    for (int i = 0; i < videoTitles.size(); ++i) {
        QListWidgetItem *item = new QListWidgetItem(feedListWidget);
        item->setSizeHint(QSize(250, 200));

        QWidget *videoItemWidget = new QWidget(feedListWidget);
        videoItemWidget->setStyleSheet("background-color: #f5f5f5; border: 1px solid #ccc; border-radius: 8px; margin: 5px;");

        QVBoxLayout *itemLayout = new QVBoxLayout(videoItemWidget);

        QLabel *thumbnailLabel = new QLabel(videoItemWidget);
        thumbnailLabel->setPixmap(QPixmap("path_to_thumbnail").scaled(150, 100, Qt::KeepAspectRatio, Qt::SmoothTransformation));
        thumbnailLabel->setAlignment(Qt::AlignCenter);
        itemLayout->addWidget(thumbnailLabel);

        QLabel *titleLabel = new QLabel(videoTitles.at(i), videoItemWidget);
        titleLabel->setAlignment(Qt::AlignCenter);
        titleLabel->setStyleSheet("font-weight: bold; margin-top: 5px;");
        itemLayout->addWidget(titleLabel);

        QLabel *sharerLabel = new QLabel("Shared by: " + sharers.at(i), videoItemWidget);
        sharerLabel->setAlignment(Qt::AlignCenter);
        sharerLabel->setStyleSheet("font-style: italic; color: #888;");
        itemLayout->addWidget(sharerLabel);

        QMediaPlayer *player = new QMediaPlayer;
        QVideoWidget *videoWidget = new QVideoWidget(videoItemWidget);
        itemLayout->addWidget(videoWidget);

        // Replace "path_to_video" with the actual path or URL
        QMediaContent mediaContent(QUrl::fromLocalFile("qrc:/feedvids/Ownvids/Baby dog.mp4"));
        player->setMedia(mediaContent);

        connect(feedListWidget, &QListWidget::itemClicked, this, [=]() {
            player->setVideoOutput(videoWidget);
            player->setMedia(mediaContent);
            player->play();
        });

        feedListWidget->setItemWidget(item, videoItemWidget);
    }

    connect(feedListWidget, &QListWidget::itemClicked, this, [this]() { Q_UNUSED(this); });

    layout->addWidget(feedListWidget);

    page->setLayout(layout);
}


void MainWindow::SetupAddVideoPage(QWidget *page) {
    QVBoxLayout *layout = new QVBoxLayout(page);

    // Create camera
    QCamera *camera = new QCamera(this);

    // Create viewfinder to display the camera feed
    QCameraViewfinder *viewfinder = new QCameraViewfinder(this);
    viewfinder->setMinimumSize(640, 480); // Set the size as per your requirement

    // Set the camera for the viewfinder
    camera->setViewfinder(viewfinder);

    // Create a custom round button for recording
    RecordButton *recordButton = new RecordButton(this);



    // Create a button to freeze/unfreeze the screen
    QPushButton *freezeButton = new QPushButton("Start Camera / Stop Camera", this);
    connect(freezeButton, &QPushButton::clicked, this, [camera, viewfinder]() {
        // Toggle between freezing and unfreezing the screen
        if (camera->state() == QCamera::ActiveState) {
            camera->stop();
            viewfinder->setEnabled(false);
        } else {
            camera->start();
            viewfinder->setEnabled(true);
        }
    });

    // Use a vertical layout to arrange camera components
    QVBoxLayout *cameraLayout = new QVBoxLayout;
    cameraLayout->addWidget(viewfinder);
    cameraLayout->addWidget(recordButton, 0, Qt::AlignHCenter);  // Center the record button

    // Add camera layout and buttons to the main layout
    layout->addLayout(cameraLayout);
    layout->addWidget(freezeButton);

    // Set the layout for the page
    page->setLayout(layout);

    // Set the camera as a member variable if you need to access it later
    // this->camera = camera;
}




void MainWindow::SetupProfilePage(QWidget *page){
    QVBoxLayout *layout = new QVBoxLayout(page);
    // 1st Layer: Top left - Button to go to settings
    QPushButton *settingsButton = new QPushButton(awesome->icon("fa-gear"), "Settings", this);
    connect(settingsButton, &QPushButton::clicked, this, [this](){ goToPage(5); });

    // 1st Layer: Top center - Large text "Profile"
    QLabel *profileLabel = new QLabel("Your Profile", this);
    profileLabel->setStyleSheet("font-size: 16pt;");
    profileLabel->setAlignment(Qt::AlignCenter);

    // 1st Layer: Top right - Button to log out
    QPushButton *logoutButton = new QPushButton(awesome->icon("fa-right-from-bracket"), "Logout", this);
    connect(logoutButton, &QPushButton::clicked, this, &MainWindow::logout);

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


    // Set the layout for the profile widget as a vertical layout

    layout->addLayout(layer1Layout);
    layout->addStretch(1);
    layout->addLayout(layer2Layout);
    layout->addLayout(layer3Layout);
    layout->addLayout(layer4Layout);
    layout->addStretch(2);
    layout->addLayout(layer5Layout);
    layer5Layout->setAlignment(Qt::AlignHCenter);




    // Set the profile widget as the central widget
    page->setLayout(layout);

    qDebug("Showing Profile section");
}




void MainWindow::SetupGalleryPage(QWidget *page) {
    QVBoxLayout *layout = new QVBoxLayout(page);

    // Set up video player
    mediaPlayer.setVideoOutput(&videoWidget);

    // Create a media playlist and add video files to it
    QMediaPlaylist *playlist = new QMediaPlaylist;
    playlist->addMedia(QUrl("qrc:/videos/videos/c.mp4"));
    playlist->addMedia(QUrl("qrc:/videos/videos/e.mp4"));
    playlist->addMedia(QUrl("qrc:/videos/videos/g.mp4"));
    // Add more videos as needed
    playlist->setPlaybackMode(QMediaPlaylist::Loop);

    // Set the playlist to the media player
    mediaPlayer.setPlaylist(playlist);

    // Connect play/pause button to toggle playback
    QPushButton *playPauseButton = new QPushButton("Play/Pause", page);
    connect(playPauseButton, &QPushButton::clicked, [this](){
        if (mediaPlayer.state() == QMediaPlayer::PlayingState)
            mediaPlayer.pause();
        else
            mediaPlayer.play();
    });

    // Connect media player state changes to update button text
    connect(&mediaPlayer, &QMediaPlayer::stateChanged, [playPauseButton](QMediaPlayer::State state){
        playPauseButton->setText(state == QMediaPlayer::PlayingState ? "Pause" : "Play");
    });

    // Create and set up the volume slider with a green color
    volumeSlider.setOrientation(Qt::Horizontal);
    volumeSlider.setRange(0, 100); // Set the range from 0 to 100
    volumeSlider.setValue(50);     // Set the initial volume
    volumeSlider.setStyleSheet("QSlider::groove:horizontal { background: #4CAF50; border: 1px solid #4CAF50; height: 8px; border-radius: 4px; } QSlider::handle:horizontal { background: #ffffff; border: 1px solid #4CAF50; width: 18px; height: 18px; margin: -8px 0; border-radius: 9px; }");
    connect(&volumeSlider, &QSlider::valueChanged, this, &MainWindow::updateVolume);

    // Create and set up the position slider with a green color
    positionSlider.setOrientation(Qt::Horizontal);
    positionSlider.setStyleSheet("QSlider::groove:horizontal { background: #4CAF50; border: 1px solid #4CAF50; height: 8px; border-radius: 4px; } QSlider::handle:horizontal { background: #ffffff; border: 1px solid #4CAF50; width: 18px; height: 18px; margin: -8px 0; border-radius: 9px; }");
    connect(&positionSlider, &QSlider::sliderMoved, this, &MainWindow::setPosition);

    // Connect position slider to media player
    connect(&mediaPlayer, &QMediaPlayer::positionChanged, &positionSlider, &QSlider::setValue);

    // Connect durationChanged signal to update position slider maximum value
    connect(&mediaPlayer, &QMediaPlayer::durationChanged, &positionSlider, &QSlider::setMaximum);

    // Create and set up the skip buttons
    buttonSkipPrevious.setText("Previous");
    connect(&buttonSkipPrevious, &QPushButton::clicked, this, &MainWindow::goToPreviousVideo);

    buttonSkipNext.setText("Next");
    connect(&buttonSkipNext, &QPushButton::clicked, this, &MainWindow::goToNextVideo);

    // Connect media player state changes to update skip buttons
    connect(&mediaPlayer, &QMediaPlayer::stateChanged, [this](){
        buttonSkipPrevious.setEnabled(mediaPlayer.position() > 2000); // Enable previous button if more than 2 seconds into the video
        buttonSkipNext.setEnabled(true); // Always enable next button
    });

    // Add the video widget, play/pause button, volume slider, position slider, and skip buttons to the layout
    layout->addWidget(&videoWidget);
    layout->addWidget(playPauseButton);
    layout->addWidget(&volumeSlider);
    layout->addWidget(&positionSlider);

    QHBoxLayout *buttonLayout = new QHBoxLayout;
    buttonLayout->addWidget(&buttonSkipPrevious);
    buttonLayout->addWidget(&buttonSkipNext);
    layout->addLayout(buttonLayout);

    // Set the background color of the page to green
    page->setStyleSheet("background-color: #D3D3D3;");

    // Set the layout for the page
    page->setLayout(layout);
}





void MainWindow::SetupLoginPage(QWidget *page){
    QWidget *container = new QWidget(page);
    QVBoxLayout *mainLayout = new QVBoxLayout(container);

    QWidget *loginForm = new QWidget(container);
    loginForm->setObjectName("loginForm");
    loginForm->setStyleSheet("#loginForm {\
                                background-color: #f1f1f1;\
                                border: 1px solid #ccc;\
                                border-radius: 3px;\
                                padding: 50px;\
                            }");

    QVBoxLayout *loginFormVBox = new QVBoxLayout(loginForm);

    QLabel *loginLabel = new QLabel("Sign In", loginForm);
    loginLabel->setStyleSheet("font-size: 28pt;");

    QLabel *descriptionLabel = new QLabel("Please enter your credentials to sign in", loginForm);

    QLineEdit *username = new QLineEdit(loginForm);
    username->setPlaceholderText("Username");

    QLineEdit *password = new QLineEdit(loginForm);
    password->setPlaceholderText("Password");

    QCheckBox *rememberMe = new QCheckBox("Remember me", loginForm);

    QPushButton *loginButton = new QPushButton("Sign In", loginForm);
    loginButton->setStyleSheet("background-color: #4CAF50;\
                                color: white;\
                                padding: 14px 20px;\
                                margin: 8px 0;\
                                border: none;\
                                border-radius: 4px;\
                                cursor: pointer;\
                                font-size: 16px;");
    connect(loginButton, &QPushButton::clicked, this, &MainWindow::login);

    QLabel *forgotPassword = new QLabel("<a href=\"#\">Forgot your password?</a>", loginForm);
    forgotPassword->setStyleSheet("font-size: 12pt;");

    QLabel *signUp = new QLabel("<a href=\"#\">Don't have an account? Sign up</a>", loginForm);
    signUp->setStyleSheet("font-size: 12pt;");

    loginFormVBox->addWidget(loginLabel);
    loginFormVBox->addWidget(descriptionLabel);
    loginFormVBox->addWidget(username);
    loginFormVBox->addWidget(password);
    loginFormVBox->addWidget(rememberMe);
    loginFormVBox->addWidget(loginButton);
    loginFormVBox->addWidget(forgotPassword);
    loginFormVBox->addWidget(signUp);

    mainLayout->addWidget(loginForm, 1, Qt::AlignHCenter | Qt::AlignVCenter);

    // Center the container widget on the page
    QVBoxLayout *containerLayout = new QVBoxLayout(page);
    containerLayout->addWidget(container, 1, Qt::AlignHCenter | Qt::AlignVCenter);

    qDebug("Showing Login page");
}



void MainWindow::SetupSettingsPage(QWidget *page){
    QVBoxLayout *layout = new QVBoxLayout(page);

    QPushButton *backButton = new QPushButton(awesome->icon("fa-chevron-left"), "Back", page);
    connect(backButton, &QPushButton::clicked, this, [this](){ goToPage(3); });
    layout->addWidget(backButton);

    QLabel *settingsLabel = new QLabel("Settings", page);
    settingsLabel->setStyleSheet("font-size: 28pt;");
    layout->addWidget(settingsLabel);

    addSettingSwitch(layout, "Wi-Fi", "Enable Wi-Fi");
    addSettingSwitch(layout, "Bluetooth", "Enable Bluetooth");
    addSettingSwitch(layout, "Notifications", "Enable Notifications");

    page->setLayout(layout);

    qDebug("Showing Settings page");
}

void MainWindow::addSettingSwitch(QVBoxLayout *layout, const QString &settingName, const QString &settingDescription) {
    QWidget *settingWidget = new QWidget;
    QHBoxLayout *settingLayout = new QHBoxLayout(settingWidget);

    QLabel *settingLabel = new QLabel(settingDescription, settingWidget);

    QCheckBox *settingSwitch = new QCheckBox(settingWidget);

    settingLayout->addWidget(settingLabel);
    settingLayout->addWidget(settingSwitch);

    layout->addWidget(settingWidget);
}

void MainWindow::login() {
    buttonPage4->setVisible(true);
    buttonPage5->setVisible(false);
    goToPage(3);
}

void MainWindow::logout() {
    buttonPage4->setVisible(false);
    buttonPage5->setVisible(true);
    goToPage(4);
}

void MainWindow::goToPreviousVideo() {
    int currentIndex = mediaPlayer.playlist()->currentIndex();
    if (currentIndex > 0) {
        mediaPlayer.playlist()->previous();
    }
}

void MainWindow::goToNextVideo() {
    int currentIndex = mediaPlayer.playlist()->currentIndex();
    if (currentIndex < mediaPlayer.playlist()->mediaCount() - 1) {
        mediaPlayer.playlist()->next();
    }
}

void MainWindow::updateVolume(int volume) {
    mediaPlayer.setVolume(volume);
}

void MainWindow::setPosition(int position) {
    mediaPlayer.setPosition(position);
}




void MainWindow::goToPreviousPage() {
    int currentIndex = stackedWidget.currentIndex();
    if (currentIndex > 0) {
        stackedWidget.setCurrentIndex(currentIndex - 1);
    }
}

void MainWindow::goToNextPage() {
    int currentIndex = stackedWidget.currentIndex();
    if (currentIndex < stackedWidget.count() - 1) {
        stackedWidget.setCurrentIndex(currentIndex + 1);
    }
}

void MainWindow::goToPage(int index) {
    stackedWidget.setCurrentIndex(index);
}

