#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QWidget>
#include <QStackedWidget>
#include <QPushButton>

class MainWindow : public QWidget {
    Q_OBJECT

public:
    MainWindow();

private slots:
    void goToPreviousPage();
    void goToNextPage();
    void goToPage(int index);
    void SetupFeedPage();

private:
    QStackedWidget stackedWidget;
    QPushButton buttonPrevious;
    QPushButton buttonNext;
    QPushButton buttonPage1;
    QPushButton buttonPage2;
    QPushButton buttonPage3;
    QPushButton buttonPage4;
    QPushButton buttonPage5;
    QPushButton buttonPage6;
};

#endif // MAINWINDOW_H




