#include "login.hpp"
#include "ui_login.h"
#include <iostream>

login::login(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::login)
{
    ui->setupUi(this);
}

login::~login()
{
    delete ui;
}

void login::on_loginButton_clicked()
{
    this->username = this->ui->EUsername->text();
    this->password = this->ui->EPassword->text();
    qDebug() << "username: " << this->username << "\n";
    qDebug() << "password: " << this->password << "\n";
    if(this->username != "" && this->password != "")
        emit this->sigValidLogin();
    else
        emit this->sigFaultyLogin();
}

void login::on_redirSignUp_clicked()
{
    emit sigRedirSignup();
}

