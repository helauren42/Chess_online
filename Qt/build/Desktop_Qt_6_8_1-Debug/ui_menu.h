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
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QLabel *label;
    QLabel *label_2;
    QPushButton *pushButton_3;
    QLineEdit *lineEdit;
    QFrame *line;
    QFrame *line_2;

    void setupUi(QWidget *Menu)
    {
        if (Menu->objectName().isEmpty())
            Menu->setObjectName("Menu");
        Menu->resize(640, 480);
        pushButton = new QPushButton(Menu);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(350, 130, 151, 25));
        pushButton_2 = new QPushButton(Menu);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(130, 130, 151, 25));
        label = new QLabel(Menu);
        label->setObjectName("label");
        label->setGeometry(QRect(300, 60, 41, 31));
        label_2 = new QLabel(Menu);
        label_2->setObjectName("label_2");
        label_2->setGeometry(QRect(300, 240, 71, 31));
        pushButton_3 = new QPushButton(Menu);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(400, 290, 151, 25));
        lineEdit = new QLineEdit(Menu);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(140, 290, 141, 25));
        line = new QFrame(Menu);
        line->setObjectName("line");
        line->setGeometry(QRect(0, 30, 641, 20));
        line->setFrameShape(QFrame::Shape::HLine);
        line->setFrameShadow(QFrame::Shadow::Sunken);
        line_2 = new QFrame(Menu);
        line_2->setObjectName("line_2");
        line_2->setGeometry(QRect(0, 220, 641, 20));
        line_2->setFrameShape(QFrame::Shape::HLine);
        line_2->setFrameShadow(QFrame::Shadow::Sunken);

        retranslateUi(Menu);

        QMetaObject::connectSlotsByName(Menu);
    } // setupUi

    void retranslateUi(QWidget *Menu)
    {
        Menu->setWindowTitle(QCoreApplication::translate("Menu", "Form", nullptr));
        pushButton->setText(QCoreApplication::translate("Menu", "Single Player(vs AI)", nullptr));
        pushButton_2->setText(QCoreApplication::translate("Menu", "2 players", nullptr));
        label->setText(QCoreApplication::translate("Menu", "Local", nullptr));
        label_2->setText(QCoreApplication::translate("Menu", "Online", nullptr));
        pushButton_3->setText(QCoreApplication::translate("Menu", "invite", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Menu: public Ui_Menu {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MENU_H
