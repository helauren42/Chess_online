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
    QPushButton *pushButton_3;
    QLineEdit *lineEdit;
    QFrame *line;
    QFrame *line_2;
    QPushButton *hotseat;
    QPushButton *logOut;

    void setupUi(QWidget *Menu)
    {
        if (Menu->objectName().isEmpty())
            Menu->setObjectName("Menu");
        Menu->resize(638, 525);
        AI = new QPushButton(Menu);
        AI->setObjectName("AI");
        AI->setGeometry(QRect(380, 190, 151, 25));
        Llocal = new QLabel(Menu);
        Llocal->setObjectName("Llocal");
        Llocal->setGeometry(QRect(300, 120, 41, 31));
        Lonline = new QLabel(Menu);
        Lonline->setObjectName("Lonline");
        Lonline->setGeometry(QRect(300, 330, 71, 31));
        pushButton_3 = new QPushButton(Menu);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(390, 390, 151, 25));
        lineEdit = new QLineEdit(Menu);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(120, 390, 141, 25));
        line = new QFrame(Menu);
        line->setObjectName("line");
        line->setGeometry(QRect(0, 70, 641, 20));
        line->setFrameShape(QFrame::Shape::HLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);
        line_2 = new QFrame(Menu);
        line_2->setObjectName("line_2");
        line_2->setGeometry(QRect(0, 280, 641, 20));
        line_2->setFrameShape(QFrame::Shape::HLine);
        line_2->setFrameShadow(QFrame::Shadow::Sunken);
        hotseat = new QPushButton(Menu);
        hotseat->setObjectName("hotseat");
        hotseat->setGeometry(QRect(110, 190, 151, 25));
        logOut = new QPushButton(Menu);
        logOut->setObjectName("logOut");
        logOut->setGeometry(QRect(20, 30, 101, 25));

        retranslateUi(Menu);

        QMetaObject::connectSlotsByName(Menu);
    } // setupUi

    void retranslateUi(QWidget *Menu)
    {
        Menu->setWindowTitle(QCoreApplication::translate("Menu", "Form", nullptr));
        AI->setText(QCoreApplication::translate("Menu", "Single Player(vs AI)", nullptr));
        Llocal->setText(QCoreApplication::translate("Menu", "Local", nullptr));
        Lonline->setText(QCoreApplication::translate("Menu", "Online", nullptr));
        pushButton_3->setText(QCoreApplication::translate("Menu", "invite", nullptr));
        hotseat->setText(QCoreApplication::translate("Menu", "2 player(hotseat)", nullptr));
        logOut->setText(QCoreApplication::translate("Menu", "logout", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Menu: public Ui_Menu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MENU_H
