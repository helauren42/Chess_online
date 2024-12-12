#include "mainwindow.hpp"
#include <QDebug>
#include <QFile>
#include <QDir>

int main(int argc, char *argv[])
{
    qDebug() << QDir::currentPath();
    QFile file("../../styles.qss");
    if (!file.open(QFile::ReadOnly | QFile::Text)) {
        qDebug() << "Failed to open stylesheet file";
        return -1;
    }

    QString stylesheet = file.readAll();

    QApplication app(argc, argv);
    app.setStyleSheet(stylesheet);
    MainWindow window(nullptr);
    window.show();

    app.exec();
    return 0;
}
