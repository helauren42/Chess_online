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

void signup::setState() {
    if(state_message == "") {
        QMessageBox::information(this, "Signup", "Account created successfully!");
    }
    else {
        QMessageBox::information(this, "Signup", "Account creation failed, check your internet and try again");
    }
	this->ui->state->setText(this->state_message);
	QPalette palette = this->ui->state->palette();
	palette.setColor(QPalette::WindowText, Qt::red);
	this->ui->state->setPalette(palette);
}

void signup::on_signUpButton_clicked()
{
	this->username = this->ui->EUsername->text();
	this->password = this->ui->EPassword->text();
	this->dob = this->ui->EDOB->date();
	qDebug() << "username: " << this->username;
	qDebug() << "password: " << this->password;
	qDebug() << "dob: " << this->dob;
    this->sigCreateAccount(username.toStdString(), password.toStdString(), dob.toString().toStdString());
}

void signup::on_redirLogIn_clicked()
{
	emit sigRedirLogin();
}
