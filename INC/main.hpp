#pragma once

#include "MyCppLib/MyCppLib.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "events.hpp"
#include "Board.hpp"
#include "Pieces.hpp"

// The x-coordinate corresponds to the file (columns), labeled a to h from left to right.
// The y-coordinate corresponds to the rank (rows), numbered 1 to 8 from bottom to top.
// 0,0 is bottom left

using namespace std;

typedef struct s_dim {
	int window;
	int board;
	int square;
} t_dim;

struct t_textures {
	SDL_Texture*	b_pawn = nullptr;
	SDL_Texture*	b_rook = nullptr;
	SDL_Texture*	b_knight = nullptr;
	SDL_Texture*	b_bishop = nullptr;
	SDL_Texture*	b_queen = nullptr;
	SDL_Texture*	b_king = nullptr;
	
	SDL_Texture*	w_pawn = nullptr;
	SDL_Texture*	w_rook = nullptr;
	SDL_Texture*	w_knight = nullptr;
	SDL_Texture*	w_bishop = nullptr;
	SDL_Texture*	w_queen = nullptr;
	SDL_Texture*	w_king = nullptr;

	SDL_Texture*	darkSquare = nullptr;
	SDL_Texture*	lightSquare = nullptr;

	SDL_Texture*	board = nullptr;

	t_textures() {}
	~t_textures() {}
	int initSquares(SDL_Renderer* renderer) {
		darkSquare = IMG_LoadTexture(renderer, "./IMG/USE/square_brown_dark.png");
		lightSquare = IMG_LoadTexture(renderer, "./IMG/USE/square_brown_light.png");
		if(!darkSquare || !lightSquare)
			return -1;
		return 0;
	}

	int initPieces(SDL_Renderer* renderer) {
		b_pawn = IMG_LoadTexture(renderer, "./IMG/USE/b_pawn.png");
		b_rook = IMG_LoadTexture(renderer, "./IMG/USE/b_rook.png");
		b_knight = IMG_LoadTexture(renderer, "./IMG/USE/b_knight.png");
		b_bishop = IMG_LoadTexture(renderer, "./IMG/USE/b_bishop.png");
		b_queen = IMG_LoadTexture(renderer, "./IMG/USE/b_queen.png");
		b_king = IMG_LoadTexture(renderer, "./IMG/USE/b_king.png");
		w_pawn = IMG_LoadTexture(renderer, "./IMG/USE/w_pawn.png");
		w_rook = IMG_LoadTexture(renderer, "./IMG/USE/w_rook.png");
		w_knight = IMG_LoadTexture(renderer, "./IMG/USE/w_knight.png");
		w_bishop = IMG_LoadTexture(renderer, "./IMG/USE/w_bishop.png");
		w_queen = IMG_LoadTexture(renderer, "./IMG/USE/w_queen.png");
		w_king = IMG_LoadTexture(renderer, "./IMG/USE/w_king.png");
	}

	int initChessBoard(SDL_Renderer* renderer, SDL_Texture* darkSquare, SDL_Texture* lightSquare, t_dim dim) {
		board = SDL_CreateTexture(
			renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
			dim.board, dim.board);

		if (!board) {
			SDL_Log("Failed to create board texture: %s", SDL_GetError());
			return -1;
		}
		SDL_SetRenderTarget(renderer, board);

		for (int row = 0; row < 8; ++row) {
			for (int col = 0; col < 8; ++col) {
				SDL_Texture* currentSquare = (row + col) % 2 == 0 ? lightSquare : darkSquare;
				SDL_Rect dstRect = { col * dim.square, row * dim.square, dim.square, dim.square };
				SDL_RenderCopy(renderer, currentSquare, NULL, &dstRect);
			}
		}
		SDL_SetRenderTarget(renderer, NULL);
		return 0;
	}

	int initFoundationTextures(SDL_Renderer* renderer, t_dim dim) {
		if(initSquares(renderer) || initPieces(renderer) || initChessBoard(renderer, darkSquare, lightSquare, dim))
			return -1;
	}

};

enum PieceType {
	PAWN,
	ROOK,
	KNIGHT,
	BISHOP,
	QUEEN,
	KING
};

enum {
	BLACK,
	WHITE
};

struct Move
{
	short x;
	short y;
};

struct Pos
{
public:
	Pos()
	{
		x = 0;
		y = 0;
		xyToFr();
	};
	Pos(short _x, short _y)
	{
		x = _x;
		y = _y;
		xyToFr();
	};
	short x;
	short y;
	string file_rank;

	void setPos(short _x, short _y)
	{
		x = _x;
		y = _y;
		if(!validPos())
			throw (std::invalid_argument("Position not valid"));
		xyToFr();
	};

	void setPos(string _fr)
	{
		file_rank = _fr;
		frToXy();
	};

	bool validPos() { return x >= 0 && x <= 7 && y >= 0 && y <= 7; }

private:
	void frToXy()
	{
		x = file_rank[0] - 97;
		y = file_rank[1] - 49;
	}
	void xyToFr()
	{
		file_rank[0] = x + 97;
		file_rank[1] = y + 49;
	}
};

Move operator-(Pos new_pos, Pos old_pos)
{
	Move move;
	move.x = new_pos.x - old_pos.x;
	move.y = new_pos.y - old_pos.y;
	return move;
}

Pos operator+(Pos pos, Move move)
{
	pos.setPos(pos.x + move.x, pos.y + move.y);
	return pos;
}

std::ostream& operator<<(std::ostream& os, const Pos& pos) {
	os << pos.file_rank << endl;
	os << "x: " << pos.x << endl;
	os << "y: " << pos.y << endl;
	return os;
}

bool operator==(Pos pos1, Pos pos2) {
	return pos1.x == pos2.x && pos1.y == pos2.y;
}
