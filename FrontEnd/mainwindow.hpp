#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "common.hpp"
#include "login.hpp"
#include "signup.hpp"
#include "menu.hpp"
#include "game.hpp"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MStackedWidgets : public QStackedWidget {
public:
    login* widLogin;
    signup* widSignup;
    Menu* widMenu;
    Game* widGame;
    MStackedWidgets();
    ~MStackedWidgets();
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MStackedWidgets* stackedWidgets;
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void sigOpenMenu();
    void sigStartGame();

private slots:
    void onSigLogin();
    void onValidLogin();
    void onFaultyLogin();

    void onSigSignup();

    void onOpenMenu();
    void onLaunchGame();

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
