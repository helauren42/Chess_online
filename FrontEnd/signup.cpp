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
	QPalette palette = this->ui->state->palette();
	palette.setColor(QPalette::WindowText, Qt::red);
	if(state_message == "") {
        palette.setColor(QPalette::WindowText, Qt::green);
		state_message == "Account created successfully!";
	}
	
	this->ui->state->setPalette(palette);
	this->ui->state->setText(this->state_message);
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
