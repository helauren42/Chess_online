#include "Pieces.hpp"
#include "main.hpp"
#include "memory"

class Squares {
	private:
		Pos pos;
		Pieces* piece;
	public:
		Squares(short x, short y) : pos(x, y) { piece = nullptr;};
		~Squares() {};
};

class Board {
	private:
		vector<vector<unique_ptr<Squares>>> board;
	public:
		Board() { init();};
		~Board() {};

		void init() {
			// init empty squares and pawns
			board.resize(8);
			for(short y = 0; y < 8; y++) {
				board[y].resize(8);
				for(short x = 0; x < 8; x++) {
					board[y][x] = make_unique<Squares>(x, y);

				}
			}
			// init Pawns
			
		};
};
