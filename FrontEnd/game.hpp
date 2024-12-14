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
    QPixmap lightSquare;
    QPixmap darkSquare;
    void computeDim();
    void resizeEvent(QResizeEvent* event);
    void emptySquares();    
    std::unique_ptr<Board> board;

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
};

#endif // GAME_HPP
