#include "mainwindow.hpp"
#include <QDebug>
#include <QFile>
#include <QDir>

SharedData  shared_data;
t_dim       dim;

int main(int argc, char *argv[])
{
    QString cwd = QDir::currentPath();
    qDebug() << "Current Working Directory:" << cwd;

    QFile file("../../../FrontEnd/styles.css");
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