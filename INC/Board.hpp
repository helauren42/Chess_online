#ifndef BOARD_HPP
#define BOARD_HPP

#include "Pieces.hpp"
#include <memory>
#include <vector>

class Board {
	private:
		std::vector<std::unique_ptr<Pieces>> active_pieces;
		std::vector<std::unique_ptr<Pieces>> dead_white_pieces;
		std::vector<std::unique_ptr<Pieces>> dead_black_pieces;
	public:
		Board() { init();};
		~Board() {};

		const std::vector<std::unique_ptr<Pieces>>& getActivePieces() const { return active_pieces; }
		std::unique_ptr<Pieces>	initPiece(const short& x, const short& y) {
			// make piece
			std::unique_ptr<Pieces> piece;
			if(y == 1 || y == 6) {
				piece = std::make_unique<Pawn>(x, y);
			}
			else if(x == 0 || x == 7) {
				piece = std::make_unique<Rook>(x, y);
			}
			else if(x == 1 || x == 6) {
				piece = std::make_unique<Knight>(x, y);
			}
			else if(x == 2 || x == 5) {
				piece = std::make_unique<Bishop>(x, y);
			}
			else if(x == 3) {
				piece = std::make_unique<Queen>(x, y);
			}
			else if(x == 4) {
				piece = std::make_unique<King>(x, y);
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

#endif