/********************************************************************************
** Form generated from reading UI file 'menu.ui'
**
** Created by: Qt User Interface Compiler version 6.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MENU_H
#define UI_MENU_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Menu
{
public:
    QPushButton *AI;
    QLabel *Llocal;
    QLabel *Lonline;
    QPushButton *onlineInvite;
    QLineEdit *onlineForm;
    QFrame *line;
    QPushButton *hotseat;
    QPushButton *logOut;
    QFrame *line_2;
    QLabel *onlinePlayersList;

    void setupUi(QWidget *Menu)
    {
        if (Menu->objectName().isEmpty())
            Menu->setObjectName("Menu");
        Menu->resize(638, 525);
        AI = new QPushButton(Menu);
        AI->setObjectName("AI");
        AI->setGeometry(QRect(90, 250, 151, 25));
        Llocal = new QLabel(Menu);
        Llocal->setObjectName("Llocal");
        Llocal->setGeometry(QRect(160, 90, 41, 31));
        Lonline = new QLabel(Menu);
        Lonline->setObjectName("Lonline");
        Lonline->setGeometry(QRect(450, 90, 71, 31));
        onlineInvite = new QPushButton(Menu);
        onlineInvite->setObjectName("onlineInvite");
        onlineInvite->setGeometry(QRect(530, 170, 71, 25));
        onlineForm = new QLineEdit(Menu);
        onlineForm->setObjectName("onlineForm");
        onlineForm->setGeometry(QRect(350, 170, 141, 25));
        line = new QFrame(Menu);
        line->setObjectName("line");
        line->setGeometry(QRect(0, 70, 641, 20));
        line->setFrameShape(QFrame::Shape::HLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);
        hotseat = new QPushButton(Menu);
        hotseat->setObjectName("hotseat");
        hotseat->setGeometry(QRect(100, 160, 151, 25));
        logOut = new QPushButton(Menu);
        logOut->setObjectName("logOut");
        logOut->setGeometry(QRect(560, 30, 61, 25));
        line_2 = new QFrame(Menu);
        line_2->setObjectName("line_2");
        line_2->setGeometry(QRect(290, 0, 71, 521));
        line_2->setFrameShape(QFrame::Shape::VLine);
        line_2->setFrameShadow(QFrame::Shadow::Sunken);
        onlinePlayersList = new QLabel(Menu);
        onlinePlayersList->setObjectName("onlinePlayersList");
        onlinePlayersList->setGeometry(QRect(360, 230, 231, 231));

        retranslateUi(Menu);

        QMetaObject::connectSlotsByName(Menu);
    } // setupUi

    void retranslateUi(QWidget *Menu)
    {
        Menu->setWindowTitle(QCoreApplication::translate("Menu", "Form", nullptr));
        AI->setText(QCoreApplication::translate("Menu", "Single Player(vs AI)", nullptr));
        Llocal->setText(QCoreApplication::translate("Menu", "Local", nullptr));
        Lonline->setText(QCoreApplication::translate("Menu", "Online", nullptr));
        onlineInvite->setText(QCoreApplication::translate("Menu", "invite", nullptr));
        hotseat->setText(QCoreApplication::translate("Menu", "2 player(hotseat)", nullptr));
        logOut->setText(QCoreApplication::translate("Menu", "logout", nullptr));
        onlinePlayersList->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class Menu: public Ui_Menu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MENU_H