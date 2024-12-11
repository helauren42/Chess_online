#include "mainwindow.hpp"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_submit_clicked()
{
    QString firstName = ui->firstText->toPlainText();
    QString lastName = ui->lastText->toPlainText();

    this->close();
}

