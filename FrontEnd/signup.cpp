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

void signup::setFaultyState() {
	this->ui->state->setText(this->error_message);
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
	std::pair<std::string, int> response = Global::online.createAccount(username.toStdString(), password.toStdString(), dob.toString().toStdString());
	int code = response.second;
	std::string body = response.first;
	if(code == 200) {
        error_message = "";
        this->setFaultyState();
		QMessageBox::information(this, "Signup", "Account created successfully!");
	}
	else {
		std::string message = response.first;
        error_message = QString(message.substr(12, message.size() - 14).c_str());
		qDebug() << "extracted error message: " << error_message;
		this->setFaultyState();
	}
}

void signup::on_redirLogIn_clicked()
{
	emit sigRedirLogin();
}
