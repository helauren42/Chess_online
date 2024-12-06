#ifndef BOARD_HPP
#define BOARD_HPP

#include "Utils.hpp"
#include "Pieces.hpp"
#include <memory>
#include <vector>
#include "MyCppLib/Printer/Printer.hpp"

struct Cell {
	PieceType 	type = NONE;
	bool		*color = nullptr;
};

class Board {
	private:
		std::array<std::array<Cell, 8>, 8> board;
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

		void	removePiece(Pieces* piece) {
			for(auto it = active_pieces.begin(); it != active_pieces.end(); it++) {
				if(*it == piece) {
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

		bool foundObstacle(Pos old_pos, Pos new_pos, PieceType type) const {
			Move move = new_pos - old_pos;
			switch (type)
			{
				case PAWN:
					if(abs(move.y) == 1)
						return false;
					if(board[old_pos.y + move.y / 2][old_pos.x].type != NONE)
						return true;
					return false;
				case ROOK: {
					short incrX = move.x > 0 ? 1 : -1;
					short incrY = move.y > 0 ? 1 : -1;
					while((old_pos.x != new_pos.x || old_pos.y != new_pos.y)) {
						if(old_pos.x != new_pos.x)
							old_pos.x += incrX;
						if(old_pos.y != new_pos.y)
							old_pos.y += incrY;
						if(board[old_pos.y][old_pos.x].type != NONE) {
							return true;
						}
					}
					return false;
				}
				case KNIGHT:
					return false;
				case BISHOP:
					return false;
				case QUEEN:
					return false;
				case KING:
					return false;
				default:
					break;
			}
			return true;
		}

		// there is a valid move per piece, where every individual piece checks if the move is valid from their perspective
		// meaning they can move in such a way
		// then the board needs to validate the move by checking that there aren't any obstructions in the way stopping the piece from making the move
		// so a validMove() per piece and a validMove() for the board
		
		void	setBoard() {
			Cell cell;
			for(int i = 0; i < 8; i++) {
				for(int j = 0; j < 8; j++) {
					board[i][j] = cell;
				}
			}
			for(auto it = active_pieces.begin(); it != active_pieces.end(); it++) {
				Pos pos = it->get()->getPosition();
				PieceType type = it->get()->getType();
				bool color = it->get()->getColor();
				board[pos.y][pos.x].type = type;
				board[pos.y][pos.x].color = &color;
			}
		}

		bool validMove(Pos new_pos, const Pieces* piece, const Pieces* target_piece) {
			if(target_piece && piece->getColor() == target_piece->getColor())
				return false;
			setBoard();
			if(!piece->validMove(new_pos, target_piece))
				return false;
			if(foundObstacle(piece->getPosition(), new_pos, piece->getType()))
				return false;
			return true;
		}

		void	moveSelectedPiece(const short& x, const short& y) {
			fout("moving selected piece\n");
			Pos new_pos = coordinatesToPos(x, y, dim->board, dim->board);
			Pieces* target_piece = nullptr;

			for(auto it = active_pieces.begin(); it != active_pieces.end(); it++) {
				if(it->get()->getPosition() == new_pos)
					target_piece = it->get();
			}
			for(auto it = active_pieces.begin(); it != active_pieces.end(); it++) {
				if(selected_piece == it->get()) {
					if(validMove(new_pos, it->get(), target_piece)) {
						it->get()->makeMove(new_pos);
						fout("moved piece to: \n", *it);
						if(target_piece)
							removePiece(target_piece);
						selected_piece = nullptr;
						return;
					}
				}
			}
			selected_piece = nullptr;
			fout("move failed\n");
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