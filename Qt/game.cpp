#include "game.hpp"
#include "ui_game.h"

void Game::MakeChessBoard() {
    qDebug() << "MakeChessBoard()";
    qDebug() << "square len: " << square_len;

    if (squares.empty()) {
        for (int row = 0; row < 8; row++) {
            for (int col = 0; col < 8; col++) {
                QLabel* square = new QLabel(this);
                squares.push_back(square);
            }
        }
    }

    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            QLabel* square = squares[row * 8 + col];

            square->setGeometry(start_x + col * square_len, row * square_len, square_len, square_len);

            // Set the background image based on the square's color
            if ((row + col) % 2 == 0) {
                square->setPixmap(lightSquare.scaled(square_len, square_len, Qt::KeepAspectRatio));
            } else {
                square->setPixmap(darkSquare.scaled(square_len, square_len, Qt::KeepAspectRatio));
            }
        }
    }
}

void    Game::onStart() {
    MakeChessBoard();
}

void Game::computeDim() {
    this->board_len = this->_height;
    this->square_len = board_len / 8;
    this->start_x = (this->_width - this->board_len) / 2;
}

void Game::resizeEvent(QResizeEvent* event) {
    QWidget::resizeEvent(event);  // Call base class implementation

    QSize newSize = event->size();
    this->_width = newSize.width();
    this->_height = newSize.height();

    computeDim();
    MakeChessBoard();
    qDebug() << "Window resized to width: " << this->_width << "height: " << this->_height;
}

void Game::emptySquares() {
    for(auto it = squares.rbegin(); it != squares.rend(); it++) {
        (*it)->deleteLater();
    }
    squares.clear();
}

Game::Game(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Game)
{
    ui->setupUi(this);

    this->_height = this->height();
    this->_width = this->width();
    computeDim();

    lightSquare = QPixmap("../../IMG/USE/square_brown_light.png");
    darkSquare = QPixmap("../../IMG/USE/square_brown_dark.png");
}

Game::~Game()
{
    delete ui;
    emptySquares();
}
