#include "mainwindow.hpp"
#include "ui_mainwindow.h"

MStackedWidgets::MStackedWidgets() {
    loginWidget = new login();
    signupWidget = new signup();
    this->addWidget(loginWidget);
    this->addWidget(signupWidget);
}

MStackedWidgets::~MStackedWidgets() {
    delete loginWidget;
    delete signupWidget;
}

void    MainWindow::onSigLogin() {
    stackedWidgets->setCurrentWidget(stackedWidgets->loginWidget);
    this->setWindowTitle("Login");
}

void    MainWindow::onSigSignup() {
    stackedWidgets->setCurrentWidget(stackedWidgets->signupWidget);
    this->setWindowTitle("Sign up");
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Login");

    stackedWidgets = new MStackedWidgets();

    setCentralWidget(stackedWidgets);

    stackedWidgets->setCurrentWidget(stackedWidgets->loginWidget);

    connect(stackedWidgets->loginWidget, &login::sigRedirSignup, this, &MainWindow::onSigSignup);
    connect(stackedWidgets->signupWidget, &signup::sigRedirLogin, this, &MainWindow::onSigLogin);

}

MainWindow::~MainWindow()
{
    delete ui;
    delete stackedWidgets;
}
