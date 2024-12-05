#ifndef BOARD_HPP
#define BOARD_HPP

#include "Utils.hpp"
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
		t_dim *dim;
	public:
		Board() { init();};
		~Board() {};

		void setDim(t_dim &_dim) {
			dim = &_dim;
		}

		const std::vector<std::unique_ptr<Pieces>>& getActivePieces() const { return active_pieces; }
		const std::unique_ptr<Pieces>& getSelectedPiece() const { return selected_piece; }
		void	setSelectedPiece(std::unique_ptr<Pieces> piece) {
			selected_piece = std::move(piece);
		}

		void	removePiece(Pos new_pos) {
			for(auto it = active_pieces.begin(); it != active_pieces.end(); it++) {
				if(it->get()->getPosition() == new_pos) {
					if(it->get()->getColor() == BLACK) {
						dead_black_pieces.push_back(std::move(*it));
					}
					else
						dead_white_pieces.push_back(std::move(*it));
					active_pieces.erase(it);
					break;
				}
			}
		}

		void	moveSelectedPiece(const short& x, const short& y) {
			Pos new_pos = coordinatesToPos(x, y, dim->board, dim->board);
			Pieces* targetPiece = nullptr;
			for(auto it = active_pieces.begin(); it != active_pieces.end(); it++) {
				if(it->get()->getPosition() == new_pos)
					targetPiece = it->get();
			}

			for(auto it = active_pieces.begin(); it != active_pieces.end(); it++) {
				if(selected_piece == *it) {
					if(targetPiece)
						out("target: ", targetPiece);
					out("Past: ", *it);
					if(it->get()->validMove(new_pos, targetPiece)) {
						it->get()->makeMove(new_pos);
						// if(targetPiece)
						// 	removePiece(new_pos);						
					}
					// out("Future: ", *it);
					selected_piece = nullptr;
					break;
				}
			}
		}

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