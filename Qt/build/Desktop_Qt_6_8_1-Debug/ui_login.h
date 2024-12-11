/********************************************************************************
** Form generated from reading UI file 'login.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGIN_H
#define UI_LOGIN_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_login
{
public:
    QLabel *LUsername;
    QLineEdit *EUsername;
    QLineEdit *EPassword;
    QLabel *LPassword;
    QPushButton *loginButton;
    QPushButton *redirSignUp;

    void setupUi(QWidget *login)
    {
        if (login->objectName().isEmpty())
            login->setObjectName("login");
        login->resize(640, 480);
        LUsername = new QLabel(login);
        LUsername->setObjectName("LUsername");
        LUsername->setGeometry(QRect(150, 170, 91, 41));
        EUsername = new QLineEdit(login);
        EUsername->setObjectName("EUsername");
        EUsername->setGeometry(QRect(280, 180, 171, 25));
        EPassword = new QLineEdit(login);
        EPassword->setObjectName("EPassword");
        EPassword->setGeometry(QRect(280, 240, 171, 25));
        LPassword = new QLabel(login);
        LPassword->setObjectName("LPassword");
        LPassword->setGeometry(QRect(150, 230, 91, 41));
        loginButton = new QPushButton(login);
        loginButton->setObjectName("loginButton");
        loginButton->setGeometry(QRect(250, 330, 89, 25));
        redirSignUp = new QPushButton(login);
        redirSignUp->setObjectName("redirSignUp");
        redirSignUp->setGeometry(QRect(220, 70, 171, 25));

        retranslateUi(login);

        QMetaObject::connectSlotsByName(login);
    } // setupUi

    void retranslateUi(QWidget *login)
    {
        login->setWindowTitle(QCoreApplication::translate("login", "Form", nullptr));
        LUsername->setText(QCoreApplication::translate("login", "username", nullptr));
        EPassword->setText(QString());
        LPassword->setText(QCoreApplication::translate("login", "password", nullptr));
        loginButton->setText(QCoreApplication::translate("login", "Login", nullptr));
        redirSignUp->setText(QCoreApplication::translate("login", "click here to sign up", nullptr));
    } // retranslateUi

};

namespace Ui {
    class login: public Ui_login {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGIN_H
