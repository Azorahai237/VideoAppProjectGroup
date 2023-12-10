#include "mainwindow.h"
#include <QVBoxLayout>
#include <QPushButton>
#include <QListWidget>
#include <QLabel>



MainWindow::MainWindow() {
    // Create six pages
    QWidget *pages[6];

    for (int i = 0; i < 6; ++i) {
        pages[i] = new QWidget;
        QVBoxLayout *layout = new QVBoxLayout(pages[i]);
        layout->addWidget(new QPushButton("Page " + QString::number(i + 1) + " Button"));
        pages[i]->setLayout(layout);
        stackedWidget.addWidget(pages[i]);
    }

    // Connect buttons to navigate through pages
    connect(&buttonPrevious, &QPushButton::clicked, this, &MainWindow::goToPreviousPage);
    connect(&buttonNext, &QPushButton::clicked, this, &MainWindow::goToNextPage);
    connect(&buttonPage1, &QPushButton::clicked, this, [this](){ goToPage(0); });
    connect(&buttonPage2, &QPushButton::clicked, this, [this](){ goToPage(1); });
    connect(&buttonPage3, &QPushButton::clicked, this, [this](){ goToPage(2); });
    connect(&buttonPage4, &QPushButton::clicked, this, [this](){ goToPage(3); });
    connect(&buttonPage5, &QPushButton::clicked, this, [this](){ goToPage(4); });
    connect(&buttonPage6, &QPushButton::clicked, this, [this](){ goToPage(5); });

    // Create a layout for the main window
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addWidget(&stackedWidget);
    mainLayout->addWidget(&buttonPrevious);
    mainLayout->addWidget(&buttonNext);
    mainLayout->addWidget(&buttonPage1);
    mainLayout->addWidget(&buttonPage2);
    mainLayout->addWidget(&buttonPage3);
    mainLayout->addWidget(&buttonPage4);
    mainLayout->addWidget(&buttonPage5);
    mainLayout->addWidget(&buttonPage6);
    setLayout(mainLayout);
}

void MainWindow::SetupFeedPage() {
    QVBoxLayout *layout = new QVBoxLayout;

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
    setLayout(layout);
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

