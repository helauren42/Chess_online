#include "Board.hpp"

	/* ---------------------------------------------------------------------- INITIALIZATION --------------------------------------------------------------------------- */

	std::unique_ptr<Pieces> Board::initPiece(const short &x, const short &y)
	{
		// make piece
		std::unique_ptr<Pieces> piece;
		if (y == 1 || y == 6)
			piece = std::make_unique<Pawn>(x, y);
		else if (x == 0 || x == 7)
			piece = std::make_unique<Rook>(x, y);
		else if (x == 1 || x == 6)
			piece = std::make_unique<Knight>(x, y);
		else if (x == 2 || x == 5)
			piece = std::make_unique<Bishop>(x, y);
		else if (x == 3)
			piece = std::make_unique<Queen>(x, y);
		else if (x == 4)
			piece = std::make_unique<King>(x, y);
		return piece;
	}
	
	void Board::init()
	{
		for (short y = 0; y < 8; y++)
			for (short x = 0; x < 8; x++)
				if (y <= 1 || y >= 6)
					active_pieces.push_back(initPiece(x, y));
	};

	/* ---------------------------------------------------------------------- Setters and getters --------------------------------------------------------------------------- */

	void Board::setBoard()
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

	Pieces* Board::getTargetPiece(const Pos &new_pos) const
	{
		Pieces *target_piece = nullptr;

		for (auto it = active_pieces.begin(); it != active_pieces.end(); it++)
		{
			if (it->get()->getPosition() == new_pos)
				target_piece = it->get();
		}
		return target_piece;
	}

	Pieces* Board::getKing() const
	{
		for (auto it = active_pieces.begin(); it != active_pieces.end(); it++)
		{
			if (it->get()->getType() == KING && it->get()->getColor() == *player_turn)
				return it->get();
		}
		return nullptr;
	};

	/* ---------------------------------------------------------------------- Validating move --------------------------------------------------------------------------- */

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

	bool Board::foundObstacle(Pos old_pos, Pos new_pos, PieceType type, bool piece_color)
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
					return true;
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

	// there is a validMove() per piece, where every individual piece checks if the move is valid from their perspective
	// meaning they can move in such a way
	// then the board needs to validate the move by checking that there aren't any obstructions in the way stopping the piece from making the move
	// so a validMove() per piece and a validMove() for the board
	bool Board::validMove(Pos new_pos, const Pieces *piece, const Pieces *target_piece)
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
			return debug("Target piece is same color\n"), false;
		else if (!piece->validMove(new_pos, target_piece))
			return debug("Invalid move for piece\n"), false;
		else if (foundObstacle(piece->getPosition(), new_pos, piece->getType(), piece->getColor()))
			return debug("Found obstacle\n"), false;

		return true;
	}

	/* ---------------------------------------------------------------------- Making the move --------------------------------------------------------------------------- */


	void Board::removePiece(Pieces *piece)
	{
		debug("remove piece: ", piece);
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

	void Board::makeEnPassant(const Pos &old_pos, const Move &move)
	{
		Pos pos(old_pos.x, old_pos.y + move.y / 2);
		active_pieces.push_back(std::make_unique<EnPassant>(pos.x, pos.y, selected_piece->getColor()));
	}

	void Board::moveSelectedPiece(const short &x, const short &y)
	{
		castling = false;
		debug("moving selected piece\n");

		// remove the en_passant temporary piece if match selected_piece color
		for (auto it = active_pieces.begin(); it != active_pieces.end(); )
			if (it->get()->getType() == ENPASSANT && *player_turn == it->get()->getColor())
			{
				debug("removing en passant of color: ", *player_turn);
				active_pieces.erase(it);
				debug("removed\n");
			}
			else
				it++;

		Pos old_pos = selected_piece->getPosition();
		Pos new_pos = coordinatesToPos(x, y, dim->board, dim->board);
		Pieces *target_piece = getTargetPiece(new_pos);
		if(target_piece)
			debug("target: ", target_piece);
		else
			debug("no target piece found\n");

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
						debug("try castling\n");
						it->get()->makeMove(new_pos);
						target_piece->makeMove(old_pos);
						debug("castling done\n");
						return;
					}
					bool has_en_passant = it->get()->getType() == PAWN && abs(move.y) == 2 ? true : false;
					it->get()->makeMove(new_pos);
					// undo move if king is in check after move
					if (isCheck(target_piece))
					{
						it->get()->makeMove(old_pos);
						debug("Failed to move piece, king is checked\n");
						return;
					}

					if (it->get()->getType() == PAWN && (new_pos.y == 0 || new_pos.y == 7))
					{
						bool color = new_pos.y == 0 ? BLACK : WHITE;
						// should allow player to pick new piece but for now it's just a queen
						it->reset(new Queen(new_pos.x, new_pos.y, color));
					}
					if (has_en_passant)
					{
						debug("creating en passant piece\n");
						makeEnPassant(old_pos, move);
					}

					debug("Successfully moved piece: \n");
					if (target_piece)
					{
						removePiece(target_piece);
					}
					selected_piece = nullptr;
					*player_turn = *player_turn == WHITE ? BLACK : WHITE;
					moved = true;
					return;
				}
				debug("move can not be done, invalid\n");
			}
		}
		selected_piece = nullptr;
	}

