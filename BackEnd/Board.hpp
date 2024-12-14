#ifndef BOARD_HPP
#define BOARD_HPP

#include "Utils.hpp"
#include "Pieces.hpp"
#include <memory>
#include <vector>
#include <array>

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

	/* ---------------------------------------------------------------------- initialization  --------------------------------------------------------------------------- */

	std::unique_ptr<Pieces> initPiece(const short &x, const short &y);
	void init();

	/* ---------------------------------------------------------------------- getters and setters  --------------------------------------------------------------------------- */

	void setDim(t_dim &_dim) { dim = &_dim; }
	void setSelectedPiece(std::unique_ptr<Pieces> piece) { selected_piece = std::move(piece); }
	void setPlayerTurn(bool *_player_turn) { player_turn = _player_turn; }

	const std::vector<std::unique_ptr<Pieces>> &getActivePieces() const { return active_pieces; }
	const std::unique_ptr<Pieces> &getSelectedPiece() const { return selected_piece; }
	const bool &getMoved() const { return moved; }
	void setMoved(const bool _moved) { moved = _moved; }

	void setBoard();
	Pieces *getTargetPiece(const Pos &new_pos) const;
	Pieces *getKing() const;

	/* ---------------------------------------------------------------------- Validating move --------------------------------------------------------------------------- */

	bool foundObstacle(Pos old_pos, Pos new_pos, PieceType type, bool piece_color);
	bool validMove(Pos new_pos, const Pieces *piece, const Pieces *target_piece);
	std::vector<Pos> intersection(const Pos &start, const Pos &end);
	
	/* ---------------------------------------------------------------------- Making the move --------------------------------------------------------------------------- */

	void Board::removePiece(Pieces *piece);
	void makeEnPassant(const Pos &old_pos, const Move &move);
	void moveSelectedPiece(const short &x, const short &y);

	/* ---------------------------------------------------------------------- End game checks --------------------------------------------------------------------------- */

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
				debug("Piece: ", piece->getType());
				debug("pos: ", piece->getPosition());
				debug("Puts king in check\n");
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
					debug("This piece can uncheck:\n", piece);
					debug("by moving to this position: ", pos);
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

	// add is stalemate

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
		default:
			break;
		}
		return false;
	};
};

#endif
