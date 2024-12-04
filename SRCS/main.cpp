#include "../INC/Game.hpp"

int main(int argc, char* argv[]) {
	Game game;

	printf("1\n");
	if(game.initSDL())
		return 1;
	printf("2\n");

	if(game.initFoundationTextures())
		return 1;
	printf("3\n");

	game.run();

	game.close();
	return 0;
}
