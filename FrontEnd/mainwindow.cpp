#include "mainwindow.hpp"
#include "ui_mainwindow.h"

MStackedWidgets::MStackedWidgets() {
    widLogin = new login();
    widSignup = new signup();
    widMenu = new Menu();
    widGame = new Game();
    this->addWidget(widLogin);
    this->addWidget(widSignup);
    this->addWidget(widMenu);
    this->addWidget(widGame);
}

MStackedWidgets::~MStackedWidgets() {
    delete widLogin;
    delete widSignup;
    delete widMenu;
    delete widGame;
}

void    MainWindow::onSigLogin() {
    stackedWidgets->setCurrentWidget(stackedWidgets->widLogin);
    this->setWindowTitle("Login");
}

void    MainWindow::onValidLogin() {
    stackedWidgets->setCurrentWidget(stackedWidgets->widLogin);
    qDebug() << "login succesfull";
    emit this->sigOpenMenu();
}

void    MainWindow::onFaultyLogin() {
    stackedWidgets->setCurrentWidget(stackedWidgets->widLogin);
    this->stackedWidgets->widLogin->setFaultyState();
    qDebug() << "login failed";
}

void    MainWindow::onSigSignup() {
    stackedWidgets->setCurrentWidget(stackedWidgets->widSignup);
    this->setWindowTitle("Sign up");
    qDebug() << "on sig signup";
}

void MainWindow::onOpenMenu() {
    stackedWidgets->setCurrentWidget(stackedWidgets->widMenu);
    this->setWindowTitle("Menu");
    qDebug() << "on open menu";
}

void MainWindow::onLaunchGame() {
    qDebug() << "pre launch game widget";
    this->setWindowTitle("Game");
    stackedWidgets->setCurrentWidget(stackedWidgets->widGame);
    // sigStartGame();
    qDebug() << "launching game widget";
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Login");
    // this->setFixedSize(this->size());

    stackedWidgets = new MStackedWidgets();

    setCentralWidget(stackedWidgets);

    stackedWidgets->setCurrentWidget(stackedWidgets->widLogin);

    // Login
    connect(stackedWidgets->widLogin, &login::sigRedirSignup, this, &MainWindow::onSigSignup);
    connect(stackedWidgets->widLogin, &login::sigValidLogin, this, &MainWindow::onValidLogin);
    connect(stackedWidgets->widLogin, &login::sigFaultyLogin, this, &MainWindow::onFaultyLogin);

    // Signup
    connect(stackedWidgets->widSignup, &signup::sigRedirLogin, this, &MainWindow::onSigLogin);

    // Menu
    connect(this, &MainWindow::sigOpenMenu, this, &MainWindow::onOpenMenu);

    // Game
    connect(stackedWidgets->widMenu, &Menu::sigLauchGame, this, &MainWindow::onLaunchGame);
    // connect(this, &MainWindow::sigStartGame, stackedWidgets->widGame, &Game::onStart);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete stackedWidgets;
}









