#ifndef SIGNUP_H
#define SIGNUP_H

#include <QWidget>
#include <QDate>

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

private slots:
    void on_signUpButton_clicked();

    void on_redirLogIn_clicked();

private:
    QString username;
    QString password;
    QDate dob;
    Ui::signup *ui;

signals:
    void sigRedirLogin();
};

#endif // SIGNUP_H
