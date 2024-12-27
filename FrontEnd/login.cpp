#include "login.hpp"
#include "ui_login.h"
#include <Exception.h>

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

void login::setFaultyState(const QString& msg) {
	error_message = msg;
	this->ui->state->setText(this->error_message);

	QPalette palette = this->ui->state->palette();
	palette.setColor(QPalette::WindowText, Qt::red);
	this->ui->state->setPalette(palette);
}

void login::on_loginButton_clicked()
{
	std::pair<std::string, int> response;
	this->username = this->ui->EUsername->text();
	this->password = this->ui->EPassword->text();
	qDebug() << "username: " << this->username << "\n";
	qDebug() << "password: " << this->password << "\n";

    emit sigUpdateLogin(username.toStdString(), this->password.toStdString());
}

void login::on_redirSignUp_clicked()
{
	emit sigRedirSignup();
}
