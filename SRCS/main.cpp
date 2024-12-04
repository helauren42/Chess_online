#include "../INC/Game.hpp"
#include "../INC/MyCppLib/Printer/Printer.hpp"

int main(int argc, char* argv[]) {
	Game game;

	// std::cout << "initSDL" << std::endl;
	if(game.initSDL())
		return 1;

	// std::cout << "initFoundationTextures" << std::endl;
	if(game.initFoundationTextures())
		return 1;
	
	// std::cout << "run" << std::endl;
	game.run();

	// std::cout << "close" << std::endl;
	game.close();
	return 0;
}
