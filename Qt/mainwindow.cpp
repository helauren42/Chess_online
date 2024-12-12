#include "mainwindow.hpp"
#include "ui_mainwindow.h"

MStackedWidgets::MStackedWidgets() {
    widLogin = new login();
    widSignup = new signup();
    widMenu = new Menu();
    this->addWidget(widLogin);
    this->addWidget(widSignup);
    this->addWidget(widMenu);
}

MStackedWidgets::~MStackedWidgets() {
    delete widLogin;
    delete widSignup;
}

void    MainWindow::onSigLogin() {
    stackedWidgets->setCurrentWidget(stackedWidgets->widLogin);
    this->setWindowTitle("Login");
}

void    MainWindow::onValidLogin() {
    stackedWidgets->setCurrentWidget(stackedWidgets->widLogin);
    qDebug() << "login succesfull";
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

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Login");

    stackedWidgets = new MStackedWidgets();

    setCentralWidget(stackedWidgets);

    stackedWidgets->setCurrentWidget(stackedWidgets->widLogin);

    // Login
    connect(stackedWidgets->widLogin, &login::sigRedirSignup, this, &MainWindow::onSigSignup);
    connect(stackedWidgets->widLogin, &login::sigValidLogin, this, &MainWindow::onValidLogin);
    connect(stackedWidgets->widLogin, &login::sigFaultyLogin, this, &MainWindow::onFaultyLogin);

    connect(stackedWidgets->widLogin, &login::sigRedirMenu, this, &MainWindow::onOpenMenu);

    // Signup
    connect(stackedWidgets->widSignup, &signup::sigRedirLogin, this, &MainWindow::onSigLogin);

    // Menu

}

MainWindow::~MainWindow()
{
    delete ui;
    delete stackedWidgets;
}









