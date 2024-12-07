#ifndef GAME_HPP
#define GAME_HPP

#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
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

	if (SDL_GetCurrentDisplayMode(0, &display_mode) == 0)
	{
		screen_width = display_mode.w;
		screen_height = display_mode.h;
	}

	dim.window_height = screen_height * 0.9;
	dim.window_width = dim.window_height;

	window = SDL_CreateWindow(
		"SDL Example",
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		dim.window_width, dim.window_height,
		SDL_WINDOW_SHOWN);

	if (!window)
		return NULL;

	int top = 0, left = 0, bottom = 0, right = 0;
	if (SDL_GetWindowBordersSize(window, &top, &left, &bottom, &right) != 0)
	{
		printf("Failed to get window borders: %s", SDL_GetError());
		return NULL;
	}

	dim.board = dim.window_height - top - bottom;
	dim.square = dim.board / 8;
	return window;
}

class Game
{
private:
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
	bool initSDL()
	{
		if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
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
		if (textures.initSquares(renderer) || textures.initPieces(renderer) || textures.initChessBoard(renderer, textures.darkSquare, textures.lightSquare, dim))
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
		SDL_Quit();
	}

	bool gameEnd()
	{
		// add stalemate checker
		Pieces *checker = board.isCheck();
		if (!checker)
			return false;
		out("game end is checked\n");
		bool king_immobilized = board.isImmobilized(board.getKing());
		out("king immobilized: ", king_immobilized);
		if(king_immobilized == false) {
			exit(1);
			return false;
		}
		out("can uncheck bout to start\n");
		bool can_uncheck = board.canUncheck(checker);
		out("can uncheck: ", can_uncheck);
		if (king_immobilized && !can_uncheck)
		{
			winner = checker->getColor() == WHITE ? WHITE: BLACK;
			return true;
		}
		return false;
	}

	void run()
	{
		SDL_Event e;
		short winner = -1; // can be set to BLACK or WHITE
		bool quit = false;
		bool game_end = false;
		while (!quit)
		{
			SDL_RenderClear(renderer);
			SDL_RenderCopy(renderer, textures.board, NULL, NULL);
			if (board.getSelectedPiece()) 
			{
				textures.makeSelectedTexture(board.getSelectedPiece()->getPosition(), renderer, dim);
				SDL_RenderCopy(renderer, textures.selected, NULL, NULL);
			}
			else if (textures.selected)
			{
				SDL_DestroyTexture(textures.selected);
				textures.selected = nullptr;
			}
			textures.makePiecesTextures(renderer, board.getActivePieces(), dim.square);
			SDL_RenderCopy(renderer, textures.pieces, NULL, NULL);
			SDL_RenderPresent(renderer);
			while (SDL_PollEvent(&e) != 0)
			{
				events.eventHandler(e, quit, player_turn);
			}
			if(gameEnd() == true) {
				game_end = true;
				break;
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
		// DisplayResult();
	}

	void close()
	{
		freeing(renderer, window);
	}
};

#endif
