#include "menu.hpp"
#include "ui_menu.h"

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

void Menu::on_hotseat_clicked()
{
    shared_data.gameInfo->set(GameMode::HOTSEAT, "");
    this->sigLauchGame();
}

