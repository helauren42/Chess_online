#ifndef GAME_HPP
#define GAME_HPP

#include "common.hpp"
#include <QWidget>
#include <QPixmap>
#include <QLabel>
#include <QResizeEvent>
#include <QLabel>
#include "../BackEnd/inc/Board.hpp"
#include "../BackEnd/inc/Pieces.hpp"
#include "../BackEnd/inc/Utils.hpp"

namespace Ui {
class Game;
}

class Game : public QWidget
{
    Q_OBJECT

protected:
    void mouseReleaseEvent(QMouseEvent *event) override {
        qDebug() << "start x: " << start_x;
        if (event->button() == Qt::LeftButton) {
            const auto click_pos = event->pos();
            if(click_pos.x() >= start_x && click_pos.x() <= start_x + _width
                && click_pos.y() >= 0 && click_pos.y() <= _height)
                handleClick(click_pos.x(), click_pos.y());
            qDebug() << "Mouse Released at:" << event->pos();
        }
    }

public:
    explicit Game(QWidget *parent = nullptr);
    ~Game();

signals:
    void sigClickedBoard();

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
    QPixmap redSquare;
    QList<QLabel*> squares;
    std::vector<std::unique_ptr<QLabel>> square_pieces;
    const std::map<std::pair<PieceType, bool>, QPixmap> images = {
        {std::make_pair(PAWN, WHITE), QPixmap("../../../IMG/USE/w_pawn.png")},
        {std::make_pair(BISHOP, WHITE), QPixmap("../../../IMG/USE/w_bishop.png")},
        {std::make_pair(KNIGHT, WHITE), QPixmap("../../../IMG/USE/w_knight.png")},
        {std::make_pair(ROOK, WHITE), QPixmap("../../../IMG/USE/w_rook.png")},
        {std::make_pair(QUEEN, WHITE), QPixmap("../../../IMG/USE/w_queen.png")},
        {std::make_pair(KING, WHITE), QPixmap("../../../IMG/USE/w_king.png")},
        {std::make_pair(PAWN, BLACK), QPixmap("../../../IMG/USE/b_pawn.png")},
        {std::make_pair(BISHOP, BLACK), QPixmap("../../../IMG/USE/b_bishop.png")},
        {std::make_pair(KNIGHT, BLACK), QPixmap("../../../IMG/USE/b_knight.png")},
        {std::make_pair(ROOK, BLACK), QPixmap("../../../IMG/USE/b_rook.png")},
        {std::make_pair(QUEEN, BLACK), QPixmap("../../../IMG/USE/b_queen.png")},
        {std::make_pair(KING, BLACK), QPixmap("../../../IMG/USE/b_king.png")}
    };

    void MakeChessBoard();
    void MakePieces();
    void computeDim();
    void resizeEvent(QResizeEvent* event) override;
    void emptySquares();
    unsigned int count_pieces() const;

    Pos getClickedSquare(const int clicked_x, const int clicked_y) {
        Pos pos;
        int x = clicked_x - start_x;
        pos.x = x * 8 / board_len;
        pos.y = clicked_y * 8 / board_len;
        pos.y = pos.reverseY();
        // std::cout << "clicked square x: " << pos.x << ", y: " << pos.y << std::endl;
        Out::stdOut("my clicked square x: ", pos.x, ", y: ", pos.y);
        return pos;
    }

    void selectPiece(const Pos clicked_square) {
        const std::vector<std::unique_ptr<Pieces>> &active_pieces = board->getActivePieces();

        for (auto it = active_pieces.cbegin(); it != active_pieces.cend(); it++)
        {
            const std::unique_ptr<Pieces>::pointer piece = it->get();
            Pos pos = piece->getPosition();
            short pos_rev_y = pos.reverseY();
            if (piece->getColor() == board->player_turn && pos.x == clicked_square.x && pos.y == clicked_square.y)
            {
                switch (piece->getType())
                {
                case PAWN:
                    board->setSelectedPiece(std::make_unique<Pawn>(pos.x, pos.y, piece->getColor()));
                    break;
                case ROOK:
                    board->setSelectedPiece(std::make_unique<Rook>(pos.x, pos.y, piece->getColor()));
                    break;
                case KNIGHT:
                    board->setSelectedPiece(std::make_unique<Knight>(pos.x, pos.y, piece->getColor()));
                    break;
                case BISHOP:
                    board->setSelectedPiece(std::make_unique<Bishop>(pos.x, pos.y, piece->getColor()));
                    break;
                case QUEEN:
                    board->setSelectedPiece(std::make_unique<Queen>(pos.x, pos.y, piece->getColor()));
                    break;
                case KING:
                    board->setSelectedPiece(std::make_unique<King>(pos.x, pos.y, piece->getColor()));
                    break;
                default:
                    break;
                }
                return;
            }
        }
    }
    void handleClick(const int clicked_x, const int clicked_y) {
        Pos clicked_square = getClickedSquare(clicked_x, clicked_y);
        if(!board->getSelectedPiece()) {
            qDebug() << "selecting piece";
            selectPiece(clicked_square);
            std::ostringstream os;
            if(board->getSelectedPiece())
                os << board->getSelectedPiece();
            qDebug() << "click piece selected piece: " << os.str();
        }
        else {
            Out::stdOut("calling move selected piece");
            board->moveSelectedPiece(clicked_square);
        }
        MakeChessBoard();
        MakePieces();
    }
};

#endif // GAME_HPP
