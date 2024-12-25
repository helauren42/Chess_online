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

void login::setFaultyState() {
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

	try {
		response = online.login(username.toStdString(), this->password.toStdString());
	}
    catch (const Exception& e) {
        qDebug() << "Caught login error: " << e.what();
        error_message = "Could not connect to servers";
        emit this->sigFaultyLogin();
        return;
	}

	qDebug() << "status code: " << response.second;
	qDebug() << response.first;
    if(response.second == 200) {
        error_message = "";
		emit this->sigFaultyLogin(); // it is set to empty string not faulty
		emit this->sigValidLogin();
    }
    else {
		if(response.second == 0 || response.first == "") {
            error_message = "Could not connect to servers, maybe try again";
		}
		else {
			std::string message = response.first;
			error_message = QString(message.substr(12, message.size() - 14).c_str());
			qDebug() << "extracted error message: " << error_message;
		}
		emit this->sigFaultyLogin();
	}
}

void login::on_redirSignUp_clicked()
{
	emit sigRedirSignup();
}
