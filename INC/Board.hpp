#include "Pieces.hpp"
#include "main.hpp"
#include "memory"

struct Squares {
	public:
		Pos pos;
		unique_ptr<Pieces> piece;
		Squares(short x, short y) : pos(x, y) { piece = nullptr;};
		~Squares() {};
};

class Board {
	private:
		vector<vector<unique_ptr<Squares>>> board;
	public:
		Board() { init();};
		~Board() {};

		void initWhites(unique_ptr<Squares>& square, const short& x, const short& y) {
			if(y == 6) {
				square->piece = make_unique<Pawn>(x, y);
				return;
			}
			if(x == 0 || x == 7) {
				square->piece = make_unique<Rook>(x, y);
			}
			else if(x == 1 || x == 6) {
				square->piece = make_unique<Knight>(x, y);
			}
			else if(x == 2 || x == 5) {
				square->piece = make_unique<Bishop>(x, y);
			}
			else if(x == 3) {
				square->piece = make_unique<Queen>(x, y);
			}
			else if(x == 4) {
				square->piece = make_unique<King>(x, y);
			}
		}

		void	initBlacks(unique_ptr<Squares>& square, const short& x, const short& y) {
			if(y == 1) {
				square->piece = make_unique<Pawn>(x, y);
				return;
			}
			if(x == 0 || x == 7) {
				square->piece = make_unique<Rook>(x, y);
			}
			else if(x == 1 || x == 6) {
				square->piece = make_unique<Knight>(x, y);
			}
			else if(x == 2 || x == 5) {
				square->piece = make_unique<Bishop>(x, y);
			}
			else if(x == 3) {
				square->piece = make_unique<Queen>(x, y);
			}
			else if(x == 4) {
				square->piece = make_unique<King>(x, y);
			}
		}
		void init() {
			board.resize(8);
			for(short y = 0; y < 8; y++) {
				board[y].resize(8);
				for(short x = 0; x < 8; x++) {
					board[y][x] = make_unique<Squares>(x, y);
					if(y <= 1) {
						initBlacks(board[y][x], x, y);
					}
					else if(y >= 6) {
						initWhites(board[y][x], x, y);
					}
				}
			}
		};
};
