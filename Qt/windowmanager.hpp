#ifndef WINDOWMANAGER_HPP
#define WINDOWMANAGER_HPP

#include <QMainWindow>
#include <QApplication>
#include <QScreen>
#include <QWindow>
#include <QWidget>
#include <QStackedWidget>

struct Manager;
extern Manager manager;

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

struct Manager {
    State   state = LOGIN;
    bool    stateChange = true;
    Account account;
};

class WindowManager
{
public:
    WindowManager();
};

#endif // WINDOWMANAGER_HPP
