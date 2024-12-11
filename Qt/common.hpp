#ifndef COMMON_H
#define COMMON_H

#include <QMainWindow>
#include <QApplication>
#include <QScreen>
#include <QWindow>
#include <QWidget>


struct t_dim {
    QRect screenGeometry;
    short board;

    t_dim() {
        QScreen *screen = QGuiApplication::primaryScreen();
        screenGeometry = screen->geometry();
        board = screenGeometry.height();
    }
    ~t_dim() {}
};


#endif // COMMON_H
