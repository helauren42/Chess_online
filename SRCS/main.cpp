#include "../INC/main.hpp"

void	Freeing(SDL_Renderer* renderer, SDL_Texture* texture, SDL_Window* window) {
	SDL_DestroyTexture(texture);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(window);
	IMG_Quit();
	SDL_Quit();
}

SDL_Window*	initWindow(t_dim &dim) {
	SDL_DisplayMode display_mode;
	int screen_width = 0;
	int screen_height = 0;
	
	SDL_Window* window = NULL;

	if (SDL_GetCurrentDisplayMode(0, &display_mode) == 0) {
		screen_width = display_mode.w;
		screen_height = display_mode.h;
	}
	
	dim.window = screen_height * 0.9;
	
	window = SDL_CreateWindow(
		"SDL Example", 
		SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
		dim.window, dim.window,
		SDL_WINDOW_SHOWN
	);

	if (!window)
		return NULL;
	
	int top = 0, left = 0, bottom = 0, right = 0;
	if (SDL_GetWindowBordersSize(window, &top, &left, &bottom, &right) != 0) {
		SDL_Log("Failed to get window borders: %s", SDL_GetError());
		top = left = bottom = right = 0; // Fallback to zero if the function fails
	}

	dim.board = dim.window - top - bottom;
	dim.square = dim.board / 8;
	return window;
}

int main(int argc, char* argv[]) {
	Events events;

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {
		printf("SDL could not initialize! SDL_Error: %s\n", SDL_GetError());
		return -1;
	}

	t_dim dim;

	SDL_Window* window = initWindow(dim);
	if (!window) {
		printf("Window could not be created! SDL_Error: %s\n", SDL_GetError());
		SDL_Quit();
		return -1;
	}
	

	SDL_Renderer* renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer) {
		printf("Renderer could not be created! SDL_Error: %s\n", SDL_GetError());
		SDL_DestroyWindow(window); SDL_Quit();
		return -1;
	}

	if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
		printf("SDL_image could not initialize! SDL_image Error: %s\n", IMG_GetError());
		SDL_DestroyRenderer(renderer); SDL_DestroyWindow(window); SDL_Quit();
		return -1;
	}

	// making textures
	t_textures textures;
	if(textures.initSquares(renderer) == -1)
		return printf("Failed to load texture! SDL_image Error: %s\n", IMG_GetError()), -1;

	if(textures.createChessBoard(renderer, textures.darkSquare, textures.lightSquare, dim) == -1)
		return printf("Failed to load texture! SDL_image Error: %s\n", IMG_GetError()), -1;

	SDL_Event e;
	bool quit = false;
	while (!quit) {
		SDL_RenderClear(renderer);
		SDL_RenderCopy(renderer, textures.board, NULL, NULL);
		SDL_RenderPresent(renderer);
		while (SDL_PollEvent(&e) != 0) { // if there is an event do stuff
			events.eventHandler(e, quit);
		}
		SDL_Delay(16);
	}

	Freeing(renderer, textures.board, window);
	return 0;
}
