#include "feedpage.h"

FeedPage::FeedPage(QWidget *page) {
    QVBoxLayout *layout = new QVBoxLayout(page);

    // Add any additional setup code for the page here
    QListWidget *feedListWidget = new QListWidget;

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

    layout->addWidget(feedListWidget);

    // QHBoxLayout *buttonLayout = new QHBoxLayout;
    // QPushButton *feedButton = new QPushButton("Feed");
    // QPushButton *addVideoButton = new QPushButton("Add Video");
    // QPushButton *galleryButton = new QPushButton("Gallery");
    // QPushButton *profileButton = new QPushButton("Profile");

    // connect(feedButton, &QPushButton::clicked, this, [this](){ goToPage(0); });
    // connect(addVideoButton, &QPushButton::clicked, this, [this](){ goToPage(1); });
    // connect(galleryButton, &QPushButton::clicked, this, [this](){ goToPage(2); });
    // connect(profileButton, &QPushButton::clicked, this, [this](){ goToPage(3); });

    // buttonLayout->addWidget(feedButton);
    // buttonLayout->addWidget(addVideoButton);
    // buttonLayout->addWidget(galleryButton);
    // buttonLayout->addWidget(profileButton);

    // layout->addWidget(feedListWidget);
    // layout->addLayout(buttonLayout);
    page->setLayout(layout);
}
