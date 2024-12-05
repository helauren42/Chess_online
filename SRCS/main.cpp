#include "../INC/Game.hpp"
#include "../INC/MyCppLib/Printer/Printer.hpp"

int main(int argc, char* argv[]) {
	Game game;

	setFoutFd("logger.txt");
	if(game.initSDL())
		return 1;


	if(game.initFoundationTextures())
		return 1;

	game.initData();


	game.run();

	game.close();
	return 0;
}
