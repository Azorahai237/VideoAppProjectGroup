#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    MainWindow mainWindow;
    mainWindow.show();
    mainWindow.ShowLogin();
    mainWindow.ToggleToolBar(false);

    return app.exec();
}


