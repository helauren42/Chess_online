/********************************************************************************
** Form generated from reading UI file 'Signup.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SIGNUP_H
#define UI_SIGNUP_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDateEdit>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_signup
{
public:
    QLineEdit *EUsername;
    QLabel *LPassword;
    QLabel *LUsername;
    QLineEdit *EPassword;
    QPushButton *signUpButton;
    QLabel *LDOB;
    QDateEdit *EDOB;
    QPushButton *redirLogIn;

    void setupUi(QWidget *signup)
    {
        if (signup->objectName().isEmpty())
            signup->setObjectName("signup");
        signup->resize(640, 480);
        EUsername = new QLineEdit(signup);
        EUsername->setObjectName("EUsername");
        EUsername->setGeometry(QRect(290, 120, 171, 25));
        LPassword = new QLabel(signup);
        LPassword->setObjectName("LPassword");
        LPassword->setGeometry(QRect(160, 170, 91, 41));
        LUsername = new QLabel(signup);
        LUsername->setObjectName("LUsername");
        LUsername->setGeometry(QRect(160, 110, 91, 41));
        EPassword = new QLineEdit(signup);
        EPassword->setObjectName("EPassword");
        EPassword->setGeometry(QRect(290, 180, 171, 25));
        signUpButton = new QPushButton(signup);
        signUpButton->setObjectName("signUpButton");
        signUpButton->setGeometry(QRect(240, 340, 89, 25));
        LDOB = new QLabel(signup);
        LDOB->setObjectName("LDOB");
        LDOB->setGeometry(QRect(158, 230, 91, 41));
        EDOB = new QDateEdit(signup);
        EDOB->setObjectName("EDOB");
        EDOB->setGeometry(QRect(370, 237, 91, 30));
        redirLogIn = new QPushButton(signup);
        redirLogIn->setObjectName("redirLogIn");
        redirLogIn->setGeometry(QRect(210, 50, 171, 25));

        retranslateUi(signup);

        QMetaObject::connectSlotsByName(signup);
    } // setupUi

    void retranslateUi(QWidget *signup)
    {
        signup->setWindowTitle(QCoreApplication::translate("signup", "Form", nullptr));
        LPassword->setText(QCoreApplication::translate("signup", "password", nullptr));
        LUsername->setText(QCoreApplication::translate("signup", "username", nullptr));
        EPassword->setText(QString());
        signUpButton->setText(QCoreApplication::translate("signup", "Sign Up", nullptr));
        LDOB->setText(QCoreApplication::translate("signup", "Date of birth", nullptr));
        redirLogIn->setText(QCoreApplication::translate("signup", "click here to log in", nullptr));
    } // retranslateUi

};

namespace Ui {
    class signup: public Ui_signup {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIGNUP_H
