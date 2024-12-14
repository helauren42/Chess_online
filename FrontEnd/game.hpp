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

    void computeDim();
    void resizeEvent(QResizeEvent* event);
    void emptySquares();

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

    std::unique_ptr<Board> board;

    QPixmap lightSquare;
    QPixmap darkSquare;
    QList<QLabel*> squares;
    std::vector<std::unique_ptr<QLabel>> square_pieces;
    const std::map<std::tuple<PieceType, bool>, QPixmap> images = {
        {std::make_tuple(PAWN, WHITE), QPixmap("../../../IMG/USE/w_pawn.png")},
        {std::make_tuple(BISHOP, WHITE), QPixmap("../../../IMG/USE/w_bishop.png")},
        {std::make_tuple(KNIGHT, WHITE), QPixmap("../../../IMG/USE/w_knight.png")},
        {std::make_tuple(ROOK, WHITE), QPixmap("../../../IMG/USE/w_rook.png")},
        {std::make_tuple(QUEEN, WHITE), QPixmap("../../../IMG/USE/w_queen.png")},
        {std::make_tuple(KING, WHITE), QPixmap("../../../IMG/USE/w_king.png")},
        {std::make_tuple(PAWN, BLACK), QPixmap("../../../IMG/USE/b_pawn.png")},
        {std::make_tuple(BISHOP, BLACK), QPixmap("../../../IMG/USE/b_bishop.png")},
        {std::make_tuple(KNIGHT, BLACK), QPixmap("../../../IMG/USE/b_knight.png")},
        {std::make_tuple(ROOK, BLACK), QPixmap("../../../IMG/USE/b_rook.png")},
        {std::make_tuple(QUEEN, BLACK), QPixmap("../../../IMG/USE/b_queen.png")},
        {std::make_tuple(KING, BLACK), QPixmap("../../../IMG/USE/b_king.png")}
    };
};

#endif // GAME_HPP
