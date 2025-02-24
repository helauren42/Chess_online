#ifndef GAME_HPP
#define GAME_HPP

#include <QWidget>
#include <QPixmap>
#include <QLabel>
#include <QResizeEvent>
#include <QLabel>
#include "../BackEnd/inc/Board.hpp"
#include "../BackEnd/inc/Pieces.hpp"
#include "../BackEnd/inc/Utils.hpp"
#include "session.hpp"

#include <memory>

namespace Ui {
class Game;
}

class Game : public QWidget
{
	Q_OBJECT

protected:
	void mouseReleaseEvent(QMouseEvent *event) override {
		Out::stdOut("Mouse release event");
        qDebug() << "game mode: " << (int)session.game_info.mode;
		if(session.game_info.mode == GAMEMODE::HOTSEAT) {
			const auto click_pos = event->pos();
			if(click_pos.x() >= start_x && click_pos.x() <= start_x + _width
				&& click_pos.y() >= 0 && click_pos.y() <= _height) {
					Pos clicked_square = getClickedSquare(click_pos.x(), click_pos.y());
					handleClick(clicked_square);
				}
			Out::stdOut("Mouse Released at:", event->pos().x(), " ", event->pos().y());
			return;
		}
		qDebug() << "player turn: " << this->board->player_turn;
		qDebug() << "player color: " << session.game_info.color;
		if((session.game_info.mode == GAMEMODE::ONLINE || session.game_info.mode == GAMEMODE::AI)
			&& session.game_info.color != this->board->player_turn)
			return;
		if (event->button() == Qt::LeftButton) {
			const auto click_pos = event->pos();
			if(click_pos.x() >= start_x && click_pos.x() <= start_x + _width
				&& click_pos.y() >= 0 && click_pos.y() <= _height) {
					Pos clicked_square = getClickedSquare(click_pos.x(), click_pos.y());
					session.sendClickedSquare(clicked_square.x, clicked_square.y);
					handleClick(clicked_square);
				}
			Out::stdOut("Mouse Released at:", event->pos().x(), " ", event->pos().y());
		}
	}

public:
	explicit Game(QWidget *parent = nullptr);
	~Game();

signals:
	void sigClickedBoard();
    void sigRedirMenu();

public slots:
	void onStartGame();
    void onHandleClick(const Pos& clicked_square) {
		qDebug() << "on handle click";
        this->handleClick(clicked_square);
    }

    void onOpponentDisconnection() {
        qDebug("on opponent disconnection");
        QMessageBox *msgBox = new QMessageBox(this);
        msgBox->setWindowTitle("Opponent disconnection");
        msgBox->setText(session.game_info.opponent.c_str() + QString(" has disconnected from the game"));
        msgBox->exec();
        emit sigRedirMenu();
    }

    void onLeaveGame() {
        qDebug("on leave game");
        if(session.game_info.mode == GAMEMODE::ONLINE) {
            session.closeOnlineGame();
        }
        session.game_info.reset();
        emit sigRedirMenu();
		qDebug() << "post sig redir menu";
    }

    void on_MenuButton_clicked();

	void emptySquares();

    void setHotseatBoard();
    void setOnlineBoard();

private slots:
    void on_Restart_clicked();

private:
	Ui::Game *ui;
	int _height;
	int _width;
	int board_len;
	int square_len;
	int start_x;

	bool is_finished;

    std::unique_ptr<Board> hotseat_board = nullptr;
    std::unique_ptr<Board> online_board = nullptr;
    Board* board = nullptr;
    // std::unique_ptr<Board> ai_board = nullptr;

	QPixmap lightSquare;
	QPixmap darkSquare;
	QPixmap redSquare;
	QList<QLabel*> squares;
	std::vector<std::unique_ptr<QLabel>> square_pieces;
	const std::map<std::pair<PieceType, bool>, QPixmap> images = {
		{std::make_pair(PAWN, PLAYER_COLOR::WHITE), QPixmap("./IMG/USE/w_pawn.png")},
		{std::make_pair(BISHOP, PLAYER_COLOR::WHITE), QPixmap("./IMG/USE/w_bishop.png")},
		{std::make_pair(KNIGHT, PLAYER_COLOR::WHITE), QPixmap("./IMG/USE/w_knight.png")},
		{std::make_pair(ROOK, PLAYER_COLOR::WHITE), QPixmap("./IMG/USE/w_rook.png")},
		{std::make_pair(QUEEN, PLAYER_COLOR::WHITE), QPixmap("./IMG/USE/w_queen.png")},
		{std::make_pair(KING, PLAYER_COLOR::WHITE), QPixmap("./IMG/USE/w_king.png")},
		{std::make_pair(PAWN, PLAYER_COLOR::BLACK), QPixmap("./IMG/USE/b_pawn.png")},
		{std::make_pair(BISHOP, PLAYER_COLOR::BLACK), QPixmap("./IMG/USE/b_bishop.png")},
		{std::make_pair(KNIGHT, PLAYER_COLOR::BLACK), QPixmap("./IMG/USE/b_knight.png")},
		{std::make_pair(ROOK, PLAYER_COLOR::BLACK), QPixmap("./IMG/USE/b_rook.png")},
		{std::make_pair(QUEEN, PLAYER_COLOR::BLACK), QPixmap("./IMG/USE/b_queen.png")},
		{std::make_pair(KING, PLAYER_COLOR::BLACK), QPixmap("./IMG/USE/b_king.png")}
	};

	// const std::map<std::pair<PieceType, bool>, QPixmap> images = {
	// 	{std::make_pair(PAWN, PLAYER_COLOR::WHITE), QPixmap("../../../IMG/USE/w_pawn.png")},
	// 	{std::make_pair(BISHOP, PLAYER_COLOR::WHITE), QPixmap("../../../IMG/USE/w_bishop.png")},
	// 	{std::make_pair(KNIGHT, PLAYER_COLOR::WHITE), QPixmap("../../../IMG/USE/w_knight.png")},
	// 	{std::make_pair(ROOK, PLAYER_COLOR::WHITE), QPixmap("../../../IMG/USE/w_rook.png")},
	// 	{std::make_pair(QUEEN, PLAYER_COLOR::WHITE), QPixmap("../../../IMG/USE/w_queen.png")},
	// 	{std::make_pair(KING, PLAYER_COLOR::WHITE), QPixmap("../../../IMG/USE/w_king.png")},
	// 	{std::make_pair(PAWN, PLAYER_COLOR::BLACK), QPixmap("../../../IMG/USE/b_pawn.png")},
	// 	{std::make_pair(BISHOP, PLAYER_COLOR::BLACK), QPixmap("../../../IMG/USE/b_bishop.png")},
	// 	{std::make_pair(KNIGHT, PLAYER_COLOR::BLACK), QPixmap("../../../IMG/USE/b_knight.png")},
	// 	{std::make_pair(ROOK, PLAYER_COLOR::BLACK), QPixmap("../../../IMG/USE/b_rook.png")},
	// 	{std::make_pair(QUEEN, PLAYER_COLOR::BLACK), QPixmap("../../../IMG/USE/b_queen.png")},
	// 	{std::make_pair(KING, PLAYER_COLOR::BLACK), QPixmap("../../../IMG/USE/b_king.png")}
	// };

	void MakeChessBoard();
	void MakePieces();
	void computeDim();
	void resizeEvent(QResizeEvent* event) override;
	unsigned int count_pieces() const;

	Pos getClickedSquare(const int clicked_x, const int clicked_y) {
		Pos pos;
		int x = clicked_x - start_x;
		pos.x = x * 8 / board_len;
		pos.y = clicked_y * 8 / board_len;
		pos.y = pos.reverseY();
		Out::stdOut("my clicked square x: ", pos.x, ", y: ", pos.y);
		return pos;
	}

	void selectPiece(const Pos clicked_square) {
		const std::vector<std::unique_ptr<Pieces>> &active_pieces = board->getActivePieces();
		for (auto it = active_pieces.cbegin(); it != active_pieces.cend(); it++)
		{
			const std::unique_ptr<Pieces>::pointer piece = it->get();
			Pos pos = piece->getPosition();
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
	void handleClick(const Pos& clicked_square) {
		qDebug() << "handle click";
        qDebug() << "clicked_square x: " << clicked_square.x;
        qDebug() << "clicked_square y: " << clicked_square.y;
		if(!board->getSelectedPiece()) {
			selectPiece(clicked_square);
			std::ostringstream os;
			if(board->getSelectedPiece())
				os << board->getSelectedPiece();
			qDebug() << "click piece selected piece: " << os.str();
		}
		else {
			Out::stdOut("calling move selected piece");
			board->moveSelectedPiece(clicked_square);
			if(board->isCheckmate() || board->isStalemate())
				is_finished = true;
		}
		MakeChessBoard();
		MakePieces();
	}
};

#endif // GAME_HPP
