#include "signup.hpp"
#include "ui_signup.h"

signup::signup(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::signup)
{
    ui->setupUi(this);
}

signup::~signup()
{
    delete ui;
}

void signup::on_signUpButton_clicked()
{
    this->username = this->ui->EUsername->text();
    this->password = this->ui->EPassword->text();
    this->dob = this->ui->EDOB->date();
    qDebug() << "username: " << this->username;
    qDebug() << "password: " << this->password;
    qDebug() << "dob: " << this->dob;
}

void signup::on_redirLogIn_clicked()
{
    emit sigRedirLogin();
}
