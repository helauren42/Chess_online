#ifndef BOARD_HPP
#define BOARD_HPP

#include "Pieces.hpp"
#include <memory>
#include <vector>
#include "MyCppLib/Printer/Printer.hpp"

class Board {
	private:
		std::unique_ptr<Pieces> selected_piece = nullptr;
		std::vector<std::unique_ptr<Pieces>> active_pieces;
		std::vector<std::unique_ptr<Pieces>> dead_white_pieces;
		std::vector<std::unique_ptr<Pieces>> dead_black_pieces;
	public:
		Board() { init();};
		~Board() {};

		std::unique_ptr<Pieces> click_piece(const int x, const int y, const t_dim& dim) {
			const int square_x = x * 8 / dim.board;
			const int square_y = y * 8 / dim.board;
			for(auto it = active_pieces.begin(); it != active_pieces.end(); it++) {
				const std::unique_ptr<Pieces>::pointer piece =  it->get();
				Pos pos = piece->getPosition(); pos.y = pos.reverseY();
				if(pos.x == square_x && pos.y == square_y)
					return std::make_unique<Pieces>(*piece);
			}
			return nullptr;
		}

		const std::vector<std::unique_ptr<Pieces>>& getActivePieces() const { return active_pieces; }
		std::unique_ptr<Pieces>	initPiece(const short& x, const short& y) {
			// make piece
			std::unique_ptr<Pieces> piece;
			if(y == 1 || y == 6) {
				out("pawn");
				piece = std::make_unique<Pawn>(x, y);
			}
			else if(x == 0 || x == 7) {
				out("Rook");
				piece = std::make_unique<Rook>(x, y);
			}
			else if(x == 1 || x == 6) {
				out("Knight");
				piece = std::make_unique<Knight>(x, y);
			}
			else if(x == 2 || x == 5) {
				out("Bishop");
				piece = std::make_unique<Bishop>(x, y);
			}
			else if(x == 3) {
				out("Queen");
				piece = std::make_unique<Queen>(x, y);
			}
			else if(x == 4) {
				out("King");
				piece = std::make_unique<King>(x, y);
			}
			out(piece->getPosition());
			out(piece->getType());
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