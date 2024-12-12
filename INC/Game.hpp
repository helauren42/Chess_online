#ifndef GAME_HPP
#define GAME_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <SDL2/SDL_ttf.h>
#include "FrontEnd.hpp"
#include "Pieces.hpp"
#include "Board.hpp"
#include "stdlib.h"
// #include "Player.hpp"

#include "../INC/MyCppLib/MyCppLib.hpp"

SDL_Window *initWindow(t_dim &dim)
{
	SDL_DisplayMode display_mode;
	int screen_width = 0;
	int screen_height = 0;

	SDL_Window *window = NULL;

	if (SDL_GetDesktopDisplayMode(0, &display_mode) != 0)
	{
		printf("failed to get display mode: %s\n", SDL_GetError());
		return NULL;
	}
	screen_width = display_mode.w;
	screen_height = display_mode.h;
	
	window = SDL_CreateWindow(
		"SDL Example",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		screen_width, screen_height,
		SDL_WINDOW_FULLSCREEN);

	if (!window)
		return NULL;

	SDL_SetWindowFullscreen(window, 0);

	SDL_GetWindowSize(window, &dim.window_width, &dim.window_height);

	int top = 0, left = 0, bottom = 0, right = 0;
	if (SDL_GetWindowBordersSize(window, &top, &left, &bottom, &right) != 0)
	{
		printf("Failed to get window borders: %s", SDL_GetError());
		return NULL;
	}

	dim.window_height = screen_height - top - bottom;
	dim.window_width = screen_width - left - right;

	dim.board = dim.window_height * 0.95;
	dim.square = dim.board / 8;
	return window;
}

class Game
{
private:
	int logger_fd = -1;
	bool player_turn = WHITE;
	WINNER winner = COLOR_NONE;
	Board board;
	t_dim dim;
	SDL_Window *window = NULL;
	SDL_Renderer *renderer = NULL;
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
		SDL_Event e;
		bool quit = false;
		bool moved = false;
		bool game_end = false;
		while (!quit)
		{
			SDL_Rect rect = {0, 0, dim.board, dim.board};
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
			SDL_Delay(64);
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
			SDL_Delay(640);
		}
	}

	void destroy()
	{
		freeing(renderer, window);
		close(logger_fd);
	}
};

#endif
