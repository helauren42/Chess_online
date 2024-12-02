#include "Pieces.hpp"
#include "main.hpp"
#include "memory"

struct Squares {
	private:
		Pos pos;
		unique_ptr<Pieces> piece;
	public:
		Squares(short x, short y) : pos(x, y) { piece = nullptr;};
		~Squares() {};
};

class Board {
	private:
		vector<unique_ptr<Pieces>> active_pieces;
		vector<unique_ptr<Pieces>> dead_white_pieces;
		vector<unique_ptr<Pieces>> dead_black_pieces;
	public:
		Board() { init();};
		~Board() {};

		unique_ptr<Pieces>	initPiece(const short& x, const short& y) {
			// make piece
			unique_ptr<Pieces> piece;
			if(y == 1 || y == 6) {
				piece = make_unique<Pawn>(x, y);
			}
			else if(x == 0 || x == 7) {
				piece = make_unique<Rook>(x, y);
			}
			else if(x == 1 || x == 6) {
				piece = make_unique<Knight>(x, y);
			}
			else if(x == 2 || x == 5) {
				piece = make_unique<Bishop>(x, y);
			}
			else if(x == 3) {
				piece = make_unique<Queen>(x, y);
			}
			else if(x == 4) {
				piece = make_unique<King>(x, y);
			}
			if(y <= 1)
				piece->setColor(WHITE);
			else
				piece->setColor(BLACK);
			return piece;
		}
		void init() {
			for(short y = 0; y < 8; y++) {
				for(short x = 0; x < 8; x++) {
					if(y <= 1 || y >= 6) {
						active_pieces.push_back(initPiece(x, y));
					}
				}
			}
		};

};

