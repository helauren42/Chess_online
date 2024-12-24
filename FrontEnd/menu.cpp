#include "menu.hpp"
#include "ui_menu.h"
#include "../MyCppLib/Printer/Printer.hpp"

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

void Menu::getOnlinePlayers() {
    auto response = online.fetchOnlinePlayers();
    if(response.second != 200)
        qDebug() << "Could not fetch online players: " << response.second;
    else {
        qDebug() << "Fetched online players: ";
        Out::stdOut(response.first);
    }
    players = response.first;
}

void Menu::updateOnlinePlayers() {
    QString text;
    for (auto it = players.begin(); it != players.end(); it++) {
        text += it->second.c_str();
        text += "\n";
    }
    this->ui->onlinePlayersList->setText(text);
}

void Menu::on_hotseat_clicked()
{
    this->sigLauchGame();
}

void Menu::on_logOut_clicked()
{
    online.logout();
    emit this->sigLogOut();
}

void Menu::on_onlineInvite_clicked()
{
    QString challenged = this->ui->onlineForm->text();
    qDebug() << "challenger: " << online.account.username;
    qDebug() << "challenged: " << challenged;
    online.sendChallenge(online.account.username, challenged.toStdString());
    this->ui->onlineForm->clear();
}
