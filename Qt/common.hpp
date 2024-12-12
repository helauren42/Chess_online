#ifndef COMMON_HPP
#define COMMON_HPP

#include <QMainWindow>
#include <QApplication>
#include <QScreen>
#include <QWindow>
#include <QWidget>
#include <QStackedWidget>

#include <memory>

enum GameMode {
    HOTSEAT,
    AI,
    ONLINE
};

struct t_dim {
    QRect screenGeometry;
    short board;
    short x_mid;

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

struct Account {
    std::string username;
    std::string password;
    Date dob;
};

struct GameInfo {
    GameMode mode;
    std::string opponent;
};

class SharedData {
private:
    Account account;
    std::unique_ptr<GameInfo> gameInfo = nullptr;
public:
    void setGameInfo(GameMode _mode, std::string _opponent) {
        gameInfo = std::make_unique<GameInfo>();
        gameInfo->mode = _mode;
        gameInfo->opponent = _opponent;
    };
};

#endif
