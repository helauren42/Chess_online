#ifndef SIGNUP_HPP
#define SIGNUP_HPP

#include <QWidget>
#include <QDate>
#include <array>

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
};

#endif // SIGNUP_HPP
