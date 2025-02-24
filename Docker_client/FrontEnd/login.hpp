#ifndef LOGIN_H
#define LOGIN_H

#include "common.hpp"

namespace Ui {
class login;
}

class login : public QWidget
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();
    void setFaultyState(const QString& msg);

private slots:
    void on_loginButton_clicked();
    void on_redirSignUp_clicked();

private:
    QString error_message;
    QString username;
    QString password;
    Ui::login *ui;

signals:
    void sigValidLogin();
    void sigRedirSignup();
    void sigUpdateLogin(const std::string& username, const std::string& password);
};

#endif // LOGIN_H
