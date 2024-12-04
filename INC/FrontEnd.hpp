#include <iostream>
#include <map>
#include <vector>
#include <memory>
#include "SDL2/SDL.h"
#include "SDL2/SDL_image.h"

#include "Pieces.hpp"

typedef struct s_dim {
	int window = 0;
	int board = 0;
	int square = 0;
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

		if(!b_pawn || !b_rook || !b_knight || !b_bishop || !b_queen || !b_king || !w_pawn || !w_rook || !w_knight || !w_bishop || !w_queen || !w_king)
			return -1;
		return 0;
	}

	int initChessBoard(SDL_Renderer* renderer, SDL_Texture* darkSquare, SDL_Texture* lightSquare, t_dim dim) {
		board = SDL_CreateTexture(
			renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET,
			dim.board, dim.board);

		if (!board) {
			SDL_Log("Failed to create board texture: %s", SDL_GetError());
			return 1;
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
	bool	makePiecesTextures(SDL_Renderer* renderer, const std::vector<std::unique_ptr<Pieces>>& active_pieces) {
		for(int i = 0; i < active_pieces.size(); i++) {
			if(active_pieces[i]->getType() == PAWN)
			
		}
	}
};

class Events
{
private:
	std::map<int, bool> keys;
	void	keyEvents(const int key, bool& quit, const bool type);
public:
	Events();
	~Events();
	void	eventHandler(const SDL_Event& event, bool& quit);
	std::map<int, bool>	getKeys() const { return keys; };
};

Events::Events()
{
	keys[SDLK_w] = false;
	keys[SDLK_LCTRL] = false;
}

Events::~Events()
{
}

void	Events::eventHandler(const SDL_Event& event, bool& quit) {
	if(event.type == SDL_KEYDOWN || event.type == SDL_KEYUP) {
		bool type = event.type == 768 ? true : false;
		keyEvents(event.key.keysym.sym, quit, type);
	}
	if(event.type == SDL_QUIT) {
		quit = true;
	}
}

void	Events::keyEvents(const int key, bool& quit, const bool type) {
	if(keys.find(key) == keys.end())
		return;
	keys[key] = type;
	if(keys[SDLK_LCTRL] == true && keys[SDLK_w] == true)
		quit = true;
}

std::ostream& operator<<(std::ostream& os, const Events& events) {
	std::map<int, bool> temp = events.getKeys();
	for(auto it = temp.begin(); it != temp.end(); it++) {
		os << it->first << ": " << it->second << std::endl;
	}
	return os;
}
