#ifndef GAME_HPP
#define GAME_HPP

#include "FrontEnd.hpp"
#include "Pieces.hpp"
#include "Board.hpp"
#include "stdlib.h"
// #include "Player.hpp"

#include "MyCppLib/MyCppLib.hpp"

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
	void	setLoggerFd(const int fd) {
		logger_fd = fd;
	}

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

	void run()
	{
		bool quit = false;
		bool moved = false;
		bool game_end = false;
		while (!quit)
		{
			// while (SDL_PollEvent(&e) != 0)
			// {
			// 	events.eventHandler(e, player_turn, quit);
			// }
			// if (board.getSelectedPiece())
			// {
			// 	textures.makeSelectedTexture(board.getSelectedPiece()->getPosition(), renderer, dim);
			// 	SDL_RenderCopy(renderer, textures.selected, NULL, &rect);
			// }
			// else if (textures.selected)
			// {
			// 	SDL_DestroyTexture(textures.selected);
			// 	textures.selected = nullptr;
			// }
			// textures.makePiecesTextures(renderer, board.getActivePieces(), dim.square);
			if (board.getMoved() == true)
			{
				if (gameEnd() == true)
				{
					game_end = true;
					break;
				}
				board.setMoved(false);
			}
		}
		if (game_end)
		{
			out("WINNER is: ");
			if (winner == WHITE)
				out("WHITE\n");
			else if (winner == BLACK)
				out("BLACK\n");
			else
				out("STALEMATE\n");
		}
	}

	void destroy()
	{
		close(logger_fd);
	}
};

#endif
