#include "mainwindow.hpp"
Manager manager;
#include <QDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w(nullptr);
    qDebug() << "state: " << manager.stateChange;
    qDebug() << "manager state: " << manager.state;
    w.setWidget(manager.state);
    w.show();

    while(1){
        if(manager.stateChange) {
            // w.close();
            w.setWidget(manager.state);
            w.show();
            manager.stateChange = false;
        }


    }
    return a.exec();
}
