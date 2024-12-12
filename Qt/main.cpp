#include "mainwindow.hpp"
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w(nullptr);
    w.show();

    a.exec();
    return 0;
}
