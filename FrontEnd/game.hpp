#ifndef GAME_HPP
#define GAME_HPP

#include "common.hpp"
#include <QWidget>
#include <QPixmap>
#include <QLabel>
#include <QResizeEvent>
#include <QLabel>
#include "../BackEnd/inc/Board.hpp"
#include "../BackEnd/inc/Utils.hpp"

namespace Ui {
class Game;
}

class Game : public QWidget
{
    Q_OBJECT

public:
    explicit Game(QWidget *parent = nullptr);
    ~Game();
    void MakeChessBoard();
    void MakePieces();
    QPixmap lightSquare;
    QPixmap darkSquare;
    void computeDim();
    void resizeEvent(QResizeEvent* event);
    void emptySquares();    
    std::unique_ptr<Board> board;
    unsigned int count_pieces() const;

public slots:
    void onStartGame();

private:
    Ui::Game *ui;
    int _height;
    int _width;
    int board_len;
    int square_len;
    int start_x;
    QList<QLabel*> squares;
    QList<QLabel*> square_pieces;
};

#endif // GAME_HPP
