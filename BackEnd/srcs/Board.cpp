#include "../inc/Board.hpp"

// add check for draw if last 3 moves are the same

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

void Board::setSelectedPiece(std::unique_ptr<Pieces> piece) { selected_piece = std::move(piece); }
void Board::setPlayerTurn(bool *_player_turn) { player_turn = _player_turn; }

const std::vector<std::unique_ptr<Pieces>> &Board::getActivePieces() const { return this->active_pieces; }
const std::unique_ptr<Pieces> &Board::getSelectedPiece() const { return selected_piece; }
const std::array<std::array<Cell, 8>, 8>& Board::getCellBoard() const { return cell_board; }

void Board::setBoard()
{
	for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 8; x++) {
			cell_board[y][x].type = NONE;
		}
	}
	for (auto it = active_pieces.begin(); it != active_pieces.end(); it++)
	{
		Pos pos = it->get()->getPosition();
		PieceType type = it->get()->getType();
		bool color = it->get()->getColor();
		Out::stdOut("Piece: ", type, "\n", pos);
        std::string s = color == WHITE ? "WHITE" : "BLACK";
		cell_board[pos.y][pos.x].type = type;
        cell_board[pos.y][pos.x].color = color;
	}
}

Pieces *Board::getTargetPiece(const Pos &new_pos) const
{
	Pieces *target_piece = nullptr;

	for (auto it = active_pieces.begin(); it != active_pieces.end(); it++)
	{
		if (it->get()->getPosition() == new_pos)
			target_piece = it->get();
	}
	return target_piece;
}

Pieces *Board::getKing() const
{
	for (auto it = active_pieces.begin(); it != active_pieces.end(); it++)
	{
		if (it->get()->getType() == KING && it->get()->getColor() == player_turn)
			return it->get();
	}
	return nullptr;
};

/* ---------------------------------------------------------------------- Validating move --------------------------------------------------------------------------- */

/*
	starting position is included as an intersection but not the end position
*/
std::vector<Pos> Board::intersection(const Pos &start, const Pos &end)  const
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
    (void)piece_color;
	setBoard();
	Move move = new_pos - old_pos;
	switch (type)
	{
	case PAWN:
		if (abs(move.y) == 1)
			return false;
		if (cell_board[old_pos.y + move.y / 2][old_pos.x].type != NONE)
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
			if (cell_board[old_pos.y][old_pos.x].type != NONE)
				return true;
		}
		return false;
	}
	case KING:
		return false;
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
			if (cell_board[old_pos.y][old_pos.x].type != NONE)
				return true;
		}
		return false;
	}
	default:
		break;
	}
	return true;
}

std::vector<Pos> castlingPos(Pos king_pos, Pos rook_pos) {
	if(rook_pos.x < king_pos.x) {
		king_pos.x -= 2;
		rook_pos.x = king_pos.x + 1;
	}
	else {
		king_pos.x += 2;
		rook_pos.x = king_pos.x - 1;
	}
	std::vector<Pos> ret;
	ret.push_back(king_pos);
	ret.push_back(rook_pos);
    return ret;
}

// there is a validMove() per piece, where every individual piece checks if the move is valid from their perspective
// meaning they can move in such a way
// then the board needs to validate the move by checking that there aren't any obstructions in the way stopping the piece from making the move
// so a validMove() per piece and a validMove() for the board
bool Board::validMove(Pos new_pos, const Pieces *piece, const Pieces *target_piece)
{
	Out::stdOut("validating move");
	if (target_piece != nullptr && piece->getType() == KING && target_piece->getType() == ROOK && piece->getColor() == target_piece->getColor() && piece->getFirstMove() && target_piece->getFirstMove() && !isCheck())
	{
		std::vector<Pos> castling_pos = castlingPos(piece->getPosition(), target_piece->getPosition());
		std::vector<Pos> intersections = intersection(piece->getPosition(), castling_pos[0]);
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
		return Out::stdOut("Target piece is same color\n"), false;
	else if (!piece->validMove(new_pos, target_piece))
		return Out::stdOut("Invalid move for piece\n"), false;
	else if (foundObstacle(piece->getPosition(), new_pos, piece->getType(), piece->getColor()))
		return Out::stdOut("Found obstacle\n"), false;

	return true;
}

/* ---------------------------------------------------------------------- Making the move --------------------------------------------------------------------------- */

void Board::removePiece(Pieces *piece)
{
	Out::stdOut("remove piece: ", piece);
	if (piece->getType() == ENPASSANT)
	{
		Pos pawn_pos = piece->getPosition();
		pawn_pos.y += dynamic_cast<EnPassant *>(piece)->getDir();
		for (auto pawn_it = active_pieces.begin(); pawn_it != active_pieces.end(); pawn_it++)
		{
			if (pawn_it->get()->getType() == PAWN && pawn_it->get()->getColor() == piece->getColor() && pawn_it->get()->getPosition() == pawn_pos)
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

void Board::moveSelectedPiece(const Pos &new_pos)
{
    Out::stdOut("moving selected piece\n");
	castling = false;

	// remove the en_passant temporary piece if match selected_piece color
	for (auto it = active_pieces.begin(); it != active_pieces.end();)
		if (it->get()->getType() == ENPASSANT && player_turn == it->get()->getColor())
		{
            Out::stdOut("removing en passant of color: ", player_turn);
			active_pieces.erase(it);
		}
		else
			it++;

	Pos old_pos = selected_piece->getPosition();
	// Pos new_pos = coordinatesToPos(x, y, dim->board, dim->board);
	Pieces *target_piece = getTargetPiece(new_pos);
	if (target_piece)
        Out::stdOut("target: ", target_piece);
	else
        Out::stdOut("no target piece found");

	for (auto it = active_pieces.begin(); it != active_pieces.end(); it++)
	{
		Move move = new_pos - old_pos;
        if (selected_piece == it->get())
		{
            setBoard();
			if (validMove(new_pos, it->get(), target_piece))
            {
                Out::stdOut("Move is valid");
				if (castling == true)
				{
                    Out::stdOut("try castling");
					auto castle_pos = castlingPos(it->get()->getPosition(), target_piece->getPosition());
					it->get()->makeMove(castle_pos[0]);
					target_piece->makeMove(castle_pos[1]);
					selected_piece = nullptr;
					player_turn = player_turn == WHITE ? BLACK : WHITE;
                    Out::stdOut("castling done");
					return;
				}
				bool has_en_passant = it->get()->getType() == PAWN && abs(move.y) == 2 ? true : false;
				Out::stdOut("PRE MOVE ACTIVE PIECES SIZE: ", active_pieces.size());
				it->get()->makeMove(new_pos);
				// undo move if king is in check after move
				if (isCheck(target_piece))
				{
                    Out::stdOut("king is checked");
					it->get()->makeMove(old_pos);
                    Out::stdOut("Failed to move, move reverted, king is checked");
					return;
				}

				if (it->get()->getType() == PAWN && (new_pos.y == 0 || new_pos.y == 7))
				{
                    Out::stdOut("Pawn becomes Queen");
					bool color = new_pos.y == 0 ? BLACK : WHITE;
					// should allow player to pick new piece but for now it's just a queen
					it->reset(new Queen(new_pos.x, new_pos.y, color));
				}

				Out::stdOut("POST MOVE ACTIVE PIECES SIZE 1: ", active_pieces.size());
				if (has_en_passant)
				{
                    Out::stdOut("creating en passant piece");
					makeEnPassant(old_pos, move);
				}

                Out::stdOut("Successfully moved piece: ");
				Out::stdOut("POST MOVE ACTIVE PIECES SIZE 2: ", active_pieces.size());
				if (target_piece)
				{
                    removePiece(target_piece);
				}
				selected_piece = nullptr;
				player_turn = player_turn == WHITE ? BLACK : WHITE;
				Out::stdOut("end ACTIVE PIECES SIZE: ", active_pieces.size());
				return;
			}
            Out::stdOut("move can not be done, invalid");
		}
	}
	selected_piece = nullptr;
}

/* ---------------------------------------------------------------------- End game checks --------------------------------------------------------------------------- */

Pieces* Board::isCheck(const Pieces *target)
{
	Pieces *king = getKing();
	Pos king_pos = king->getPosition();
    for (auto &piece : active_pieces)
	{
		if (target && piece == target)
			continue;
        if (piece->getColor() != king->getColor() && validMove(king_pos, piece.get(), king))
		{
            Out::stdOut("Piece: ", piece->getType());
            Out::stdOut("pos: ", piece->getPosition());
            Out::stdOut("Puts king in check\n");
			return piece.get();
		}
	}
    Out::stdOut("no check");
	return nullptr;
}

bool Board::canUncheck(Pieces *checker)
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
				info("This piece can uncheck:\n", piece);
				info("by moving to this position: ", pos);
				return true;
			}
		}
	}
	return false;
}

bool Board::isCheckmate()
{
	Pieces *checker = isCheck();
	if (!checker)
		return false;
	if (isImmobilized(getKing()) && !canUncheck(checker)) {
		winner = player_turn == BLACK ? WHITE : BLACK;
		return true;
	}
	return false;
}

bool Board::isStalemate() {
	for (auto& piece : active_pieces) {
		if(piece->getColor() == player_turn) {
			if(!isImmobilized(piece.get()))
				return false;
		}
	}
	this->is_stalemate = true;
	return true;
}

bool Board::isImmobilized(Pieces *piece)
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
		for (auto &move : king_moves)
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
