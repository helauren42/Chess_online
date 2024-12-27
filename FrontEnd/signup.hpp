#ifndef SIGNUP_H
#define SIGNUP_H

#include "common.hpp"

namespace Ui {
class signup;
}

class signup : public QWidget
{
	Q_OBJECT

public:
	explicit signup(QWidget *parent = nullptr);
	~signup();
    void setState();

public slots:
    void onUpdateState(const QString& msg) {
        state_message = msg;
		setState();
    };

private slots:
	void on_signUpButton_clicked();
	void on_redirLogIn_clicked();

private:
	QString state_message;
	QString username;
	QString password;
	QDate dob;
	Ui::signup *ui;

signals:
	void sigRedirLogin();
	void sigCreateAccount(const std::string& username, const std::string& password, const std::string& dob);
};

#endif // SIGNUP_H
