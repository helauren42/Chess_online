#ifndef BOARD_HPP
#define BOARD_HPP

#include "Utils.hpp"
#include "Pieces.hpp"
#include <memory>
#include <vector>
#include <array>
#include "MyCppLib/Printer/Printer.hpp"

struct Cell
{
	PieceType type = NONE;
	bool *color = nullptr;
};

class Board
{
private:
	bool has_en_passant = false;
	bool *player_turn = nullptr;
	bool moved = false;
	bool castling = false;
	std::array<std::array<Cell, 8>, 8> board;
	std::unique_ptr<Pieces> selected_piece = nullptr;
	std::vector<std::unique_ptr<Pieces>> active_pieces;
	std::vector<std::unique_ptr<Pieces>> dead_white_pieces;
	std::vector<std::unique_ptr<Pieces>> dead_black_pieces;
	t_dim *dim;

public:
	Board() { init(); };
	~Board() {};

	void setDim(t_dim &_dim)
	{
		dim = &_dim;
	}

	void setSelectedPiece(std::unique_ptr<Pieces> piece)
	{
		selected_piece = std::move(piece);
	}
	void setPlayerTurn(bool *_player_turn)
	{
		player_turn = _player_turn;
	}

	const std::vector<std::unique_ptr<Pieces>> &getActivePieces() const { return active_pieces; }
	const std::unique_ptr<Pieces> &getSelectedPiece() const { return selected_piece; }
	const bool &getMoved() const { return moved; }
	void setMoved(const bool _moved) { moved = _moved; }

	Pieces *getTargetPiece(const Pos &new_pos)
	{
		Pieces *target_piece = nullptr;

		for (auto it = active_pieces.begin(); it != active_pieces.end(); it++)
		{
			if (it->get()->getPosition() == new_pos)
				target_piece = it->get();
		}
		return target_piece;
	}

	Pieces *getKing() const
	{
		for (auto it = active_pieces.begin(); it != active_pieces.end(); it++)
		{
			if (it->get()->getType() == KING && it->get()->getColor() == *player_turn)
				return it->get();
		}
		return nullptr;
	};

	std::unique_ptr<Pieces> initPiece(const short &x, const short &y)
	{
		// make piece
		std::unique_ptr<Pieces> piece;
		if (y == 1 || y == 6)
		{
			piece = std::make_unique<Pawn>(x, y);
		}
		else if (x == 0 || x == 7)
		{
			piece = std::make_unique<Rook>(x, y);
		}
		else if (x == 1 || x == 6)
		{
			piece = std::make_unique<Knight>(x, y);
		}
		else if (x == 2 || x == 5)
		{
			piece = std::make_unique<Bishop>(x, y);
		}
		else if (x == 3)
		{
			piece = std::make_unique<Queen>(x, y);
		}
		else if (x == 4)
		{
			piece = std::make_unique<King>(x, y);
		}
		return piece;
	}
	void init()
	{
		for (short y = 0; y < 8; y++)
		{
			for (short x = 0; x < 8; x++)
			{
				if (y <= 1 || y >= 6)
				{
					active_pieces.push_back(initPiece(x, y));
				}
			}
		}
	};

	void setBoard()
	{
		Cell cell;
		for (int i = 0; i < 8; i++)
		{
			for (int j = 0; j < 8; j++)
			{
				board[i][j] = cell;
			}
		}
		for (auto it = active_pieces.begin(); it != active_pieces.end(); it++)
		{
			Pos pos = it->get()->getPosition();
			PieceType type = it->get()->getType();
			bool color = it->get()->getColor();
			board[pos.y][pos.x].type = type;
			board[pos.y][pos.x].color = &color;
		}
	}

	void removePiece(Pieces *piece)
	{
		fout("remove piece: ", piece);
		if (piece->getType() == ENPASSANT)
		{
			Pos pawn_pos = piece->getPosition();
			pawn_pos.y += dynamic_cast<EnPassant*>(piece)->getDir();
			for (auto pawn_it = active_pieces.begin(); pawn_it != active_pieces.end(); pawn_it++)
			{
				if (pawn_it->get()->getType() == PAWN && pawn_it->get()->getColor() == piece->getColor() 
				&& pawn_it->get()->getPosition() == pawn_pos)
				{
					piece = pawn_it->get();
					break;
				}
			}
		}
		for (auto it = active_pieces.begin(); it != active_pieces.end(); it++)
		{
			if (*it == piece)
			{
				auto remove_it = it;

				if (it->get()->getColor() == BLACK)
				{
					dead_black_pieces.push_back(std::move(*remove_it));
				}
				else
					dead_white_pieces.push_back(std::move(*remove_it));
				active_pieces.erase(it);
				break;
			}
		}
	}

	bool foundObstacle(Pos old_pos, Pos new_pos, PieceType type, bool piece_color)
	{
		setBoard();
		Move move = new_pos - old_pos;
		switch (type)
		{
		case PAWN:
			if (abs(move.y) == 1)
				return false;
			if (board[old_pos.y + move.y / 2][old_pos.x].type != NONE)
				return true;
			return false;
		case KNIGHT:
			return false;
		case BISHOP:
		{
			short incrX = move.x > 0 ? 1 : -1;
			short incrY = move.y > 0 ? 1 : -1;
			while ((old_pos.x != new_pos.x && old_pos.y != new_pos.y))
			{
				old_pos.x += incrX;
				old_pos.y += incrY;
				if ((old_pos.x == new_pos.x && old_pos.y == new_pos.y))
					return false;
				if (board[old_pos.y][old_pos.x].type != NONE)
				{
					return true;
				}
			}
			return false;
		}
		case KING:
		{
			return false;
		}
		case ROOK:
		case QUEEN:
		{
			short incrX = move.x > 0 ? 1 : -1;
			short incrY = move.y > 0 ? 1 : -1;
			while ((old_pos.x != new_pos.x || old_pos.y != new_pos.y))
			{
				if (old_pos.x != new_pos.x)
					old_pos.x += incrX;
				if (old_pos.y != new_pos.y)
					old_pos.y += incrY;
				if ((old_pos.x == new_pos.x && old_pos.y == new_pos.y))
					return false;
				if (board[old_pos.y][old_pos.x].type != NONE)
				{
					return true;
				}
			}
			return false;
		}
		default:
			break;
		}
		return true;
	}

	// there is a valid move per piece, where every individual piece checks if the move is valid from their perspective
	// meaning they can move in such a way
	// then the board needs to validate the move by checking that there aren't any obstructions in the way stopping the piece from making the move
	// so a validMove() per piece and a validMove() for the board
	bool validMove(Pos new_pos, const Pieces *piece, const Pieces *target_piece)
	{
		if (target_piece != nullptr && piece->getType() == KING && target_piece->getType() == ROOK && piece->getColor() == target_piece->getColor() && piece->getFirstMove() && target_piece->getFirstMove() && !isCheck())
		{
			std::vector<Pos> intersections = intersection(target_piece->getPosition(), piece->getPosition());
			for (auto &square : intersections)
			{
				for (auto &active_piece : active_pieces)
				{
					if (active_piece->getColor() == piece->getColor())
						continue;
					if (validMove(square, active_piece.get(), nullptr))
						return false;
				}
			}
			castling = true;
			return true;
		}

		if (target_piece && piece->getColor() == target_piece->getColor())
		{
			fout("Target piece is same color\n");
			return false;
		}
		if (!piece->validMove(new_pos, target_piece))
		{
			fout("Invalid move for piece\n");
			return false;
		}
		if (foundObstacle(piece->getPosition(), new_pos, piece->getType(), piece->getColor()))
		{
			fout("Found obstacle\n");
			return false;
		}
		return true;
	}

	void makeEnPassant(const Pos &old_pos, const Move &move)
	{
		Pos pos(old_pos.x, old_pos.y + move.y / 2);
		active_pieces.push_back(std::make_unique<EnPassant>(pos.x, pos.y, selected_piece->getColor()));
	}

	void moveSelectedPiece(const short &x, const short &y)
	{
		castling = false;
		fout("moving selected piece\n");

		// remove_en_passant if match selected_piece color
		if (has_en_passant && selected_piece->getColor() == *player_turn)
		{
			fout("removing en passant of color: ", *player_turn);	
			for (auto it = active_pieces.begin(); it != active_pieces.end(); it++)
				if (it->get()->getType() == ENPASSANT && *player_turn == it->get()->getColor())
					active_pieces.erase(it);
		}

		Pos old_pos = selected_piece->getPosition();
		Pos new_pos = coordinatesToPos(x, y, dim->board, dim->board);
		Pieces *target_piece = getTargetPiece(new_pos);
		if(target_piece)
			fout("target: ", target_piece);
		else
			fout("no target piece found\n");

		for (auto it = active_pieces.begin(); it != active_pieces.end(); it++)
		{
			Move move = new_pos - old_pos;
			if (selected_piece == it->get())
			{
				setBoard();
				if (validMove(new_pos, it->get(), target_piece))
				{
					if (castling == true)
					{
						fout("try castling\n");
						it->get()->makeMove(new_pos);
						target_piece->makeMove(old_pos);
						fout("castling done\n");
						return;
					}
					bool has_en_passant = it->get()->getType() == PAWN && move.y == 2 ? true : false;
					it->get()->makeMove(new_pos);
					// undo move if king is in check after move
					if (isCheck(target_piece))
					{
						it->get()->makeMove(old_pos);
						fout("Failed to move piece, king is checked\n");
						return;
					}

					if (it->get()->getType() == PAWN && (new_pos.y == 0 || new_pos.y == 7))
					{
						bool color = new_pos.y == 0 ? BLACK : WHITE;
						it->reset(new Queen(new_pos.x, new_pos.y, color));
					}
					if (has_en_passant)
					{
						fout("making en passant\n");
						makeEnPassant(old_pos, move);
					}

					fout("Successfully moved piece: \n");
					if (target_piece)
					{
						removePiece(target_piece);
					}
					selected_piece = nullptr;
					*player_turn = *player_turn == WHITE ? BLACK : WHITE;
					moved = true;
					return;
				}
				fout("move can not be done, invalid\n");
			}
		}
		selected_piece = nullptr;
	}

	std::vector<Pos> intersection(const Pos &start, const Pos &end)
	{
		std::vector<Pos> ret;
		Move move = end - start;
		short incrX = 0, incrY = 0;
		if (move.x)
			incrX = move.x < 0 ? -1 : 1;
		if (move.y)
			incrY = move.y < 0 ? -1 : 1;
		Pos intersection(start.x, start.y);
		while (intersection != end)
		{
			ret.push_back(intersection);
			intersection.x += incrX;
			intersection.y += incrY;
			if (intersection == end)
				break;
		}
		return ret;
	}

	Pieces *isCheck(const Pieces *target = nullptr)
	{
		Pieces *king = getKing();
		Pos king_pos = king->getPosition();
		for (auto &piece : active_pieces)
		{
			if (target && piece == target)
				continue;
			if (piece->getColor() != king->getColor() && validMove(king_pos, piece.get(), king))
			{
				fout("Piece: ", piece->getType());
				fout("pos: ", piece->getPosition());
				fout("Puts king in check\n");
				return piece.get();
			}
		}
		return nullptr;
	}

	bool canUncheck(Pieces *checker)
	{
		Pos checker_pos = checker->getPosition();
		std::vector<Pos> intersections = intersection(checker_pos, getKing()->getPosition());
		for (auto &pos : intersections)
		{
			Pieces *target = nullptr;
			if (checker->getPosition() == pos)
				target = checker;
			for (auto &piece : active_pieces)
			{
				if (piece->getType() != KING && piece->getColor() != checker->getColor() && validMove(pos, piece.get(), target))
				{
					fout("This piece can uncheck:\n", piece);
					fout("by moving to this position: ", pos);
					return true;
				}
			}
		}
		return false;
	}

	bool isCheckmate()
	{
		Pieces *checker = isCheck();
		if (!checker)
			return false;
		if (isImmobilized(getKing()) && !canUncheck(checker))
			return true;
		return false;
	}

	bool isImmobilized(Pieces *piece)
	{
		Pos piece_pos = piece->getPosition();
		switch (piece->getType())
		{
		case PAWN:
		case ROOK:
		case BISHOP:
		case QUEEN:
		case KING:
		{
			for (int dx = -1; dx <= 1; dx++)
			{
				for (int dy = -1; dy <= 1; dy++)
				{
					Pos new_pos(piece_pos.x + dx, piece_pos.y + dy);
					if ((dx == 0 && dy == 0) || new_pos.isOutOfBounds())
						continue;
					Pieces *target = getTargetPiece(new_pos);

					if (!validMove(new_pos, piece, target))
						continue;

					if (piece->getType() != KING)
						return false;

					for (auto &piece2 : active_pieces)
					{
						if (piece2->getColor() != piece->getColor() &&
							validMove(new_pos, piece2.get(), nullptr))
						{
							return true;
						}
					}
					return false;
				}
			}
			return true;
		}
		case KNIGHT:
		{
			std::array<Move, 8> moves = {
				Move(1, 2),
				Move(1, -2),
				Move(-1, 2),
				Move(-1, -2),
				Move(2, 1),
				Move(2, -1),
				Move(-2, 1),
				Move(-2, -1)};
			for (auto &move : moves)
			{
				Pos new_pos = piece_pos + move;
				Pieces *target = getTargetPiece(new_pos);
				if (new_pos.isOutOfBounds() || !validMove(new_pos, piece, target))
					return true;
			}
			return false;
		}
		/* code */
		break;

		default:
			break;
		}
		return false;
	}
};

#endif