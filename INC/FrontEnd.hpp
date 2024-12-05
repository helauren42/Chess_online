#include <iostream>
#include <map>
#include <vector>
#include <memory>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "Pieces.hpp"
#include "Board.hpp"

typedef struct s_dim
{
	int window = 0;
	int board = 0;
	int square = 0;
} t_dim;

struct t_textures
{
	SDL_Texture *b_pawn = nullptr;
	SDL_Texture *b_rook = nullptr;
	SDL_Texture *b_knight = nullptr;
	SDL_Texture *b_bishop = nullptr;
	SDL_Texture *b_queen = nullptr;
	SDL_Texture *b_king = nullptr;

	SDL_Texture *w_pawn = nullptr;
	SDL_Texture *w_rook = nullptr;
	SDL_Texture *w_knight = nullptr;
	SDL_Texture *w_bishop = nullptr;
	SDL_Texture *w_queen = nullptr;
	SDL_Texture *w_king = nullptr;

	SDL_Texture *darkSquare = nullptr;
	SDL_Texture *lightSquare = nullptr;

	SDL_Texture *board = nullptr;

	SDL_Texture *pieces = nullptr;

	t_textures() {}
	~t_textures() {}
	int initSquares(SDL_Renderer *renderer)
	{
		darkSquare = IMG_LoadTexture(renderer, "./IMG/USE/square_brown_dark.png");
		lightSquare = IMG_LoadTexture(renderer, "./IMG/USE/square_brown_light.png");
		if (!darkSquare || !lightSquare)
			return -1;
		return 0;
	}

	int initPieces(SDL_Renderer *renderer)
	{
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

		if (!b_pawn || !b_rook || !b_knight || !b_bishop || !b_queen || !b_king || !w_pawn || !w_rook || !w_knight || !w_bishop || !w_queen || !w_king)
			return -1;
		return 0;
	}

	SDL_Texture *getPieceTexture(const PieceType type, const bool color)
	{
		if (color == BLACK)
		{
			switch (type)
			{
			case PAWN:
				return b_pawn;
			case ROOK:
				return b_rook;
			case KNIGHT:
				return b_knight;
			case BISHOP:
				return b_bishop;
			case QUEEN:
				return b_queen;
			case KING:
				return b_king;
			}
		}
		else
			switch (type)
			{
			case PAWN:
				return w_pawn;
			case ROOK:
				return w_rook;
			case KNIGHT:
				return w_knight;
			case BISHOP:
				return w_bishop;
			case QUEEN:
				return w_queen;
			case KING:
				return w_king;
			}
		return NULL;
	}

	int initChessBoard(SDL_Renderer *renderer, SDL_Texture *darkSquare, SDL_Texture *lightSquare, t_dim dim)
	{
		board = SDL_CreateTexture(
			renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
			dim.board, dim.board);

		if (!board)
		{
			SDL_Log("Failed to create board texture: %s", SDL_GetError());
			return 1;
		}
		SDL_SetRenderTarget(renderer, board);

		for (int row = 0; row < 8; row++)
		{
			for (int col = 0; col < 8; col++)
			{
				SDL_Texture *currentSquare = (row + col) % 2 == 0 ? lightSquare : darkSquare;
				SDL_Rect dstRect = {col * dim.square, row * dim.square, dim.square, dim.square};
				SDL_RenderCopy(renderer, currentSquare, NULL, &dstRect);
			}
		}
		SDL_SetRenderTarget(renderer, NULL);
		return 0;
	}

	bool makePiecesTextures(SDL_Renderer *renderer, const std::vector<std::unique_ptr<Pieces>> &active_pieces, int square_dim)
	{
		if (pieces)
			SDL_DestroyTexture(pieces);
		pieces = SDL_CreateTexture(
			renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
			square_dim * 8, square_dim * 8);

		if (!pieces)
		{
			SDL_Log("Failed to create pieces texture: %s", SDL_GetError());
			return false;
		}
		SDL_SetTextureBlendMode(pieces, SDL_BLENDMODE_BLEND);
		SDL_SetTextureBlendMode(pieces, SDL_BLENDMODE_BLEND);
		SDL_SetTextureAlphaMod(pieces, 120);
		SDL_SetRenderTarget(renderer, pieces);

		int m = square_dim / 10;
		for (size_t i = 0; i < active_pieces.size(); i++)
		{
			SDL_Texture *curr = getPieceTexture(active_pieces[i]->getType(), active_pieces[i]->getColor());
			Pos pos = active_pieces[i]->getPosition();
			SDL_Rect dstRect = {pos.x * square_dim + m, pos.reverseY() * square_dim + m, square_dim - m * 2, square_dim - m * 2};
			SDL_RenderCopy(renderer, curr, NULL, &dstRect);
		}
		SDL_SetRenderTarget(renderer, NULL);
		return true;
	}
};

class Events
{
private:
	Board *board;
	t_dim *dim;
	std::map<int, bool> keys;
	void keyEvents(const int key, bool &quit, const bool type);

public:
	Events();
	~Events();
	void setBoard(Board &_board);
	void setDim(t_dim &_dim);
	std::map<int, bool> getKeys() const { return keys; };

	void eventHandler(const SDL_Event &event, bool &quit);
	void click_piece(const int x, const int y);
};

Events::Events()
{
	keys[SDLK_w] = false;
	keys[SDLK_LCTRL] = false;
}

Events::~Events()
{
}

void Events::setBoard(Board &_board)
{
	board = &_board;
}

void Events::setDim(t_dim &_dim)
{
	dim = &_dim;
}

void Events::click_piece(const int x, const int y)
{
	const int square_x = x * 8 / dim->board;
	const int square_y = y * 8 / dim->board;
	const std::vector<std::unique_ptr<Pieces>> &active_pieces = board->getActivePieces();

	for (auto it = active_pieces.cbegin(); it != active_pieces.cend(); it++)
	{

		const std::unique_ptr<Pieces>::pointer piece = it->get();

		Pos pos = piece->getPosition();
		int pos_rev_y = pos.reverseY();
		if (pos.x == square_x && pos_rev_y == square_y)
		{
			switch (piece->getType())
			{
			case PAWN:
				board->setSelectedPiece(std::make_unique<Pawn>(pos.x, pos.y));
				break;
			case ROOK:
				board->setSelectedPiece(std::make_unique<Rook>(pos.x, pos.y));
				break;
			case KNIGHT:
				board->setSelectedPiece(std::make_unique<Knight>(pos.x, pos.y));
				break;
			case BISHOP:
				board->setSelectedPiece(std::make_unique<Bishop>(pos.x, pos.y));
				break;
			case QUEEN:
				board->setSelectedPiece(std::make_unique<Queen>(pos.x, pos.y));
				break;
			case KING:
				board->setSelectedPiece(std::make_unique<King>(pos.x, pos.y));
				break;
			default:
				break;
			}
			return;
		}
	}
	board->setSelectedPiece(nullptr);
}

void Events::eventHandler(const SDL_Event &e, bool &quit)
{
	if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP)
	{
		bool type = e.type == 768 ? true : false;
		keyEvents(e.key.keysym.sym, quit, type);
	}
	else if (e.type == SDL_QUIT)
	{
		quit = true;
	}
	else if (e.type == SDL_MOUSEBUTTONDOWN)
	{
		// if (board->getSelectedPiece() == nullptr)
			click_piece(e.button.x, e.button.y);
	}
}

void Events::keyEvents(const int key, bool &quit, const bool type)
{
	if (keys.find(key) == keys.end())
		return;
	keys[key] = type;
	if (keys[SDLK_LCTRL] == true && keys[SDLK_w] == true)
		quit = true;
}

std::ostream &operator<<(std::ostream &os, const Events &events)
{
	std::map<int, bool> temp = events.getKeys();
	for (auto it = temp.begin(); it != temp.end(); it++)
	{
		os << it->first << ": " << it->second << std::endl;
	}
	return os;
}
