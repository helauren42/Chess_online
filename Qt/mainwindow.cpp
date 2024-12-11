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

void MainWindow::setWidget(const State& state) {
    switch (state) {
    case LOGIN:
        stackedWidgets->setCurrentWidget(stackedWidgets->loginWidget);
        break;
    case SIGNUP:
        stackedWidgets->setCurrentWidget(stackedWidgets->signupWidget);
    default:
        break;
    }
}

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Login");

    stackedWidgets = new MStackedWidgets();

    setCentralWidget(stackedWidgets);
    
    this->setWidget(manager.state);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete stackedWidgets;
}
