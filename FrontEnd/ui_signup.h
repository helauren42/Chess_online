/********************************************************************************
** Form generated from reading UI file 'signup.ui'
**
** Created by: Qt User Interface Compiler version 5.15.15
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
    QLabel *state;

    void setupUi(QWidget *signup)
    {
        if (signup->objectName().isEmpty())
            signup->setObjectName(QString::fromUtf8("signup"));
        signup->resize(640, 480);
        EUsername = new QLineEdit(signup);
        EUsername->setObjectName(QString::fromUtf8("EUsername"));
        EUsername->setGeometry(QRect(290, 120, 171, 25));
        LPassword = new QLabel(signup);
        LPassword->setObjectName(QString::fromUtf8("LPassword"));
        LPassword->setGeometry(QRect(160, 170, 91, 41));
        LUsername = new QLabel(signup);
        LUsername->setObjectName(QString::fromUtf8("LUsername"));
        LUsername->setGeometry(QRect(160, 110, 91, 41));
        EPassword = new QLineEdit(signup);
        EPassword->setObjectName(QString::fromUtf8("EPassword"));
        EPassword->setGeometry(QRect(290, 180, 171, 25));
        signUpButton = new QPushButton(signup);
        signUpButton->setObjectName(QString::fromUtf8("signUpButton"));
        signUpButton->setGeometry(QRect(240, 340, 89, 25));
        LDOB = new QLabel(signup);
        LDOB->setObjectName(QString::fromUtf8("LDOB"));
        LDOB->setGeometry(QRect(158, 230, 91, 41));
        EDOB = new QDateEdit(signup);
        EDOB->setObjectName(QString::fromUtf8("EDOB"));
        EDOB->setGeometry(QRect(370, 237, 91, 30));
        redirLogIn = new QPushButton(signup);
        redirLogIn->setObjectName(QString::fromUtf8("redirLogIn"));
        redirLogIn->setGeometry(QRect(210, 50, 171, 25));
        state = new QLabel(signup);
        state->setObjectName(QString::fromUtf8("state"));
        state->setGeometry(QRect(190, 290, 361, 17));

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
        state->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class signup: public Ui_signup {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SIGNUP_H
