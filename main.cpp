#include <QApplication>
#include "mainwindow.h"

int main(int argc, char *argv[]) {
    QApplication app(argc, argv);

    // Load the stylesheet
    QFile styleFile(":/lighttheme.qss"); // Replace with the path to your stylesheet
    styleFile.open(QFile::ReadOnly | QFile::Text);
    app.setStyleSheet(styleFile.readAll());
    styleFile.close();

    MainWindow mainWindow;
    mainWindow.show();
    return app.exec();
}

