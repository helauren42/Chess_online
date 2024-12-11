/********************************************************************************
** Form generated from reading UI file 'loginwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_LOGINWINDOW_H
#define UI_LOGINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAbstractButton>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QDialogButtonBox>

QT_BEGIN_NAMESPACE

class Ui_LoginWindow
{
public:
    QDialogButtonBox *buttonSignUp;

    void setupUi(QDialog *LoginWindow)
    {
        if (LoginWindow->objectName().isEmpty())
            LoginWindow->setObjectName("LoginWindow");
        LoginWindow->resize(640, 480);
        buttonSignUp = new QDialogButtonBox(LoginWindow);
        buttonSignUp->setObjectName("buttonSignUp");
        buttonSignUp->setGeometry(QRect(10, 40, 621, 32));
        buttonSignUp->setOrientation(Qt::Orientation::Horizontal);
        buttonSignUp->setStandardButtons(QDialogButtonBox::StandardButton::Cancel|QDialogButtonBox::StandardButton::Ok);

        retranslateUi(LoginWindow);
        QObject::connect(buttonSignUp, &QDialogButtonBox::accepted, LoginWindow, qOverload<>(&QDialog::accept));
        QObject::connect(buttonSignUp, &QDialogButtonBox::rejected, LoginWindow, qOverload<>(&QDialog::reject));

        QMetaObject::connectSlotsByName(LoginWindow);
    } // setupUi

    void retranslateUi(QDialog *LoginWindow)
    {
        LoginWindow->setWindowTitle(QCoreApplication::translate("LoginWindow", "Dialog", nullptr));
    } // retranslateUi

};

namespace Ui {
    class LoginWindow: public Ui_LoginWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_LOGINWINDOW_H
