#include "../INC/Game.hpp"
#include "../INC/MyCppLib/Printer/Printer.hpp"

// add check for check, check mate
// pawns becoming queens and the special case of eating a jumping pawn
// tower king protection thing

int main(int argc, char* argv[]) {
	Game game;

	game.setLoggerFd(setFoutFd("logger.txt"));
	if(game.initSDL())
		return 1;

	if(game.initFoundationTextures())
		return 1;

	game.initData();

	game.home();

	game.run();

	game.destroy();
	return 0;
}
