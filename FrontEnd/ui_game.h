/********************************************************************************
** Form generated from reading UI file 'game.ui'
**
** Created by: Qt User Interface Compiler version 5.15.15
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_GAME_H
#define UI_GAME_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Game
{
public:
    QPushButton *MenuButton;
    QPushButton *Restart;

    void setupUi(QWidget *Game)
    {
        if (Game->objectName().isEmpty())
            Game->setObjectName(QString::fromUtf8("Game"));
        Game->resize(800, 684);
        MenuButton = new QPushButton(Game);
        MenuButton->setObjectName(QString::fromUtf8("MenuButton"));
        MenuButton->setGeometry(QRect(10, 20, 89, 25));
        Restart = new QPushButton(Game);
        Restart->setObjectName(QString::fromUtf8("Restart"));
        Restart->setGeometry(QRect(10, 70, 89, 25));

        retranslateUi(Game);

        QMetaObject::connectSlotsByName(Game);
    } // setupUi

    void retranslateUi(QWidget *Game)
    {
        Game->setWindowTitle(QCoreApplication::translate("Game", "Form", nullptr));
        MenuButton->setText(QCoreApplication::translate("Game", "Menu", nullptr));
        Restart->setText(QCoreApplication::translate("Game", "Restart", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Game: public Ui_Game {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_GAME_H
