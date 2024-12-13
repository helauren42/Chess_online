#ifndef GAME_HPP
#define GAME_HPP

#include "FrontEnd.hpp"
#include "Board.hpp"
#include "stdlib.h"
// #include "Player.hpp"


class Game
{
private:
	int logger_fd = -1;
	bool player_turn = WHITE;
	WINNER winner = COLOR_NONE;
	Board board;
	t_dim dim;
	// Player player;
public:
	Game() { board.setPlayerTurn(&player_turn); };
	~Game() {};

	bool gameEnd()
	{
		// add stalemate checker
		// for(auto &piece : board.active_pieces) {
		// 	if(!piece->isImmobilized()) {
		// 		return false;
		// 	}
		// }
		Pieces *checker = board.isCheck();
		if (board.isCheckmate())
		{
			winner = checker->getColor() == WHITE ? WHITE : BLACK;
			return true;
		}
		else {
			winner = COLOR_NONE;
		}
		return false;
	}

	void destroy()
	{
		close(logger_fd);
	}
};

#endif
