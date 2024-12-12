#ifndef GAME_HPP
#define GAME_HPP

#include <QWidget>

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

private:
    Ui::Game *ui;
};

#endif // GAME_HPP
