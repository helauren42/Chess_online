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

unsigned int Game::count_pieces() const {
    auto cells = board->getCellBoard();
    unsigned int count = 0;
    for (int y = 0; y < 8 ; y++) {
        for (int x = 0; x < 8 ; x++) {
            if(cells[y][x].type != NONE)
                count++;
        }
    }
    return count;
}

void Game::MakePieces() {
    unsigned int num_pieces = count_pieces();
    qDebug() << "MakeChessBoard()";
    qDebug() << "number of pieces: " << num_pieces;
    board->setBoard();
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

void Game::onStartGame() {
    board->init();
    MakeChessBoard();
}

Game::Game(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Game)
{
    ui->setupUi(this);

    this->_height = this->height();
    this->_width = this->width();
    computeDim();

    lightSquare = QPixmap("../../../IMG/USE/square_brown_light.png");
    darkSquare = QPixmap("../../../IMG/USE/square_brown_dark.png");
}

Game::~Game()
{
    delete ui;
    emptySquares();
}
