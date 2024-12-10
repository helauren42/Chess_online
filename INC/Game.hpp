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
	t_textures textures;
	Events events;
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
	bool initSDL()
	{
		if(TTF_Init()) {
			printf("TTF could not initialize!\n");
			return 1;
		}
		if (SDL_Init(SDL_INIT_VIDEO) < 0)
		{
			printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
			return 1;
		}
		window = initWindow(dim);
		if (!window)
		{
			printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
			SDL_Quit();
			return 1;
		}

		renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
		if (!renderer)
		{
			printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
			SDL_DestroyWindow(window);
			SDL_Quit();
			return 1;
		}

		if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
		{
			printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
			SDL_DestroyRenderer(renderer);
			SDL_DestroyWindow(window);
			SDL_Quit();
			return 1;
		}
		return 0;
	}

	int initFoundationTextures()
	{
		if (textures.initSquares(renderer) || textures.initPieces(renderer) || textures.initChessBoard(renderer, textures.darkSquare, textures.lightSquare, dim)
			|| textures.initHomeBackground(renderer, dim) || textures.initHomeLogin(renderer, dim))
			return -1;
		return 0;
	}

	void initData()
	{
		events.setBoard(board);
		events.setDim(dim);
		board.setDim(dim);
	}

	void freeing(SDL_Renderer *renderer, SDL_Window *window)
	{
		SDL_DestroyTexture(textures.b_pawn);
		SDL_DestroyTexture(textures.b_rook);
		SDL_DestroyTexture(textures.b_knight);
		SDL_DestroyTexture(textures.b_bishop);
		SDL_DestroyTexture(textures.b_queen);
		SDL_DestroyTexture(textures.b_king);
		SDL_DestroyTexture(textures.w_pawn);
		SDL_DestroyTexture(textures.w_rook);
		SDL_DestroyTexture(textures.w_knight);
		SDL_DestroyTexture(textures.w_bishop);
		SDL_DestroyTexture(textures.w_queen);
		SDL_DestroyTexture(textures.w_king);
		SDL_DestroyTexture(textures.darkSquare);
		SDL_DestroyTexture(textures.lightSquare);
		SDL_DestroyTexture(textures.board);

		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(window);
		IMG_Quit();
		TTF_Quit();
		SDL_Quit();
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
			while (SDL_PollEvent(&e) != 0)
			{
				events.eventHandler(e, player_turn, quit);
			}
			SDL_RenderClear(renderer);
			SDL_RenderCopy(renderer, textures.board, NULL, &rect);
			if (board.getSelectedPiece())
			{
				textures.makeSelectedTexture(board.getSelectedPiece()->getPosition(), renderer, dim);
				SDL_RenderCopy(renderer, textures.selected, NULL, &rect);
			}
			else if (textures.selected)
			{
				SDL_DestroyTexture(textures.selected);
				textures.selected = nullptr;
			}
			textures.makePiecesTextures(renderer, board.getActivePieces(), dim.square);
			SDL_RenderCopy(renderer, textures.pieces, NULL, &rect);
			SDL_RenderPresent(renderer);
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

	void home()
	{
		SDL_Event e;
		bool quit = false;
		while(!quit) {
			SDL_Rect rect = {0, 0, dim.window_width, dim.window_height};
			while (SDL_PollEvent(&e) != 0)
			{
				events.eventHandler(e, player_turn, quit);
			}
			SDL_RenderClear(renderer);
			SDL_RenderCopy(renderer, textures.home.background, NULL, &rect);
			// SDL_RenderCopy(renderer, textures.home.login, NULL, &rect);
			SDL_RenderPresent(renderer);
			SDL_Delay(64);
		}
	}

	void destroy()
	{
		freeing(renderer, window);
		close(logger_fd);
	}
};

#endif
