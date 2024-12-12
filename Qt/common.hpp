#ifndef COMMON_HPP
#define COMMON_HPP

#include <QMainWindow>
#include <QApplication>
#include <QScreen>
#include <QWindow>
#include <QWidget>
#include <QStackedWidget>

#include <memory>

struct SharedData;
extern SharedData shared_data;

enum GameMode {
    HOTSEAT,
    AI,
    ONLINE
};

// struct t_dim {
//     QRect screenGeometry;
//     short board;
//     short x_mid;

//     t_dim() {
//         QScreen *screen = QGuiApplication::primaryScreen();
//         screenGeometry = screen->geometry();
//         board = screenGeometry.height();
//     }
//     ~t_dim() {}
// };

struct Date {
    int day;
    int month;
    int year;
};

struct Account {
    std::string username;
    std::string password;
    Date dob;
    void set(const std::string& _username, const std::string& _password) {
        username = _username;
        password = _password;
    }
};

struct GameInfo {
    GameMode mode;
    std::string opponent;
    void set(const GameMode &_mode, const std::string _opponent = "") {
        mode = _mode;
        opponent = _opponent;
    };
};

struct SharedData {
    Account account;
    std::unique_ptr<GameInfo> gameInfo = std::make_unique<GameInfo>();
    void destroyGameInfo() {
        gameInfo = nullptr;
    }
};

#endif
