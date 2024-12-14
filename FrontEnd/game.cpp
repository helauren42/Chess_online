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
    board->setBoard();
    unsigned int num_pieces = count_pieces();
    qDebug() << "MakePieces()";
    qDebug() << "number of pieces: " << num_pieces;

    while(square_pieces.size() < num_pieces) {
        square_pieces.push_back(std::make_unique<QLabel>(this));
    }
    while(square_pieces.size() > num_pieces) {
        square_pieces.pop_back();
    }

    int i = 0;
    auto cells = board->getCellBoard();
    for (int row = 0; row < 8; row++) {
        for (int col = 0; col < 8; col++) {
            auto cell = cells[row][col];
            if(cell.type == NONE || cell.type == ENPASSANT)
                continue;
            qDebug() << "row: " << row;
            qDebug() << "col: " << col;
            QLabel* square = square_pieces[i++].get();
            square->setGeometry(start_x + col * square_len, row * square_len, square_len, square_len);
            // qDebug() << "type: " << cell.type;
            // qDebug() << "color: " << cell.color;
            square->setPixmap(images.at(std::make_tuple(cell.type, cell.color)).scaled(square_len, square_len, Qt::KeepAspectRatio));
        }
    }
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
    MakePieces();
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
    qDebug() << "here1";
    MakeChessBoard();
    qDebug() << "here2";
    MakePieces();
    qDebug() << "here3";
}

Game::Game(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Game)
{
    board = std::make_unique<Board>();
    ui->setupUi(this);

    this->_height = this->height();
    this->_width = this->width();
    computeDim();

    lightSquare = QPixmap("../../../IMG/USE/square_brown_light.png");
    qDebug() << lightSquare;
    darkSquare = QPixmap("../../../IMG/USE/square_brown_dark.png");
    qDebug() << darkSquare;
}

Game::~Game()
{
    delete ui;
    emptySquares();
}
