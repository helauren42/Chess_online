#include "menu.hpp"
#include "ui_menu.h"
#include "online.hpp"

Menu::Menu(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Menu)
{
    ui->setupUi(this);
}

Menu::~Menu()
{
    delete ui;
}

void Menu::onUpdateOnlinePlayers(QString text) {
    this->ui->onlinePlayersList->setText(text);
}

void Menu::on_hotseat_clicked()
{
    this->sigLauchGame();
}

void Menu::on_logOut_clicked()
{
    emit this->sigLogOut();
}

void Menu::on_onlineInvite_clicked()
{
    qDebug() << "clicked invite";
    emit this->sigSendChallenge(online.account.username.c_str(), this->ui->onlineForm->text());
    this->ui->onlineForm->clear();
}
