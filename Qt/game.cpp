#include "game.hpp"
#include "ui_game.h"

void Game::MakeChessBoard() {

}

Game::Game(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Game)
{
    ui->setupUi(this);

}

Game::~Game()
{
    delete ui;
}
