#ifndef LOGIN_H
#define LOGIN_H

#include "common.hpp"
#include <QWidget>

namespace Ui {
class login;
}

class login : public QWidget
{
    Q_OBJECT

public:
    explicit login(QWidget *parent = nullptr);
    ~login();
    void setFaultyState();

private slots:
    void on_loginButton_clicked();
    void on_redirSignUp_clicked();

private:
    QString username;
    QString password;
    Ui::login *ui;

signals:
    void sigValidLogin();
    void sigFaultyLogin();

    void sigRedirSignup();
    void sigRedirMenu();
};

#endif // LOGIN_H
