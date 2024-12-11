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

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    this->setWindowTitle("Login");

    stackedWidgets = new MStackedWidgets();

    setCentralWidget(stackedWidgets);

    stackedWidgets->setCurrentWidget(stackedWidgets->signupWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete stackedWidgets;
}
