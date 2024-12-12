#ifndef COMMON_H
#define COMMON_H

#include <QMainWindow>
#include <QApplication>
#include <QScreen>
#include <QWindow>
#include <QWidget>
#include <QStackedWidget>

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

struct Date {
    int day;
    int month;
    int year;
};

enum State {
    LOGIN,
    SIGNUP,
    MENU,
    GAME_OFFLINE,
    GAME_ONLINE,
};

struct Account {
    std::string username;
    std::string password;
    Date dob;
};

#endif // COMMON_H
