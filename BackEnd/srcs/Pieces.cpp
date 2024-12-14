#include "Pieces.hpp"

/* ---------------------------------------------------------------------- setters getters --------------------------------------------------------------------------- */

PieceType Pieces::getType() const { return type; }
bool Pieces::getFirstMove() const { return firstMove; }
Pos Pieces::getPosition() const { return pos; }
bool Pieces::getColor() const { return color; }


/* ---------------------------------------------------------------------- make move --------------------------------------------------------------------------- */


	void Pieces::makeMove(const Pos &new_pos)
	{
		pos = new_pos;
		firstMove = false;
	};

    bool Pawn::validMove(const Pos &new_pos, const Pieces *target) const
    {
        (void) target;
		info("new pos: ", new_pos);
		info("pos: ", pos);
		Move move = new_pos - pos;

		info("move: ", move);
		// first handle special cases
		if ((move.x == 1 || move.x == -1) && target != nullptr && (move.y == 1 * dir))
		{
			info("pawn move 1 valid\n");
			return true;
		}
		if (target != nullptr || move.x >= 2)
			return false;

		if (move.x == 0 && firstMove && move.y == 2 * dir)
		{
			info("pawn move 1 valid\n");
			return true;
		}

		if (move.x != 0 || move.y != dir)
			return false;

		info("pawn move default true\n");
		return true;
	}

	bool EnPassant::validMove(const Pos &new_pos, const Pieces *target) const
    {
        (void) new_pos;
        (void) target;
		return false;
	}

	bool Rook::validMove(const Pos &new_pos, const Pieces *target) const
	{
        (void) target;
		Move move = new_pos - pos;
		if ((move.x == 0 && move.y != 0) || (move.y == 0 && move.x != 0))
			return true;
		return false;
	}

	bool Knight::validMove(const Pos &new_pos, const Pieces *target) const
    {
        (void) target;
		Move move = new_pos - pos;
		move.x = abs(move.x);
		move.y = abs(move.y);
		if (move.x == move.y)
			return false;
		short smaller = move.x < move.y ? move.x : move.y;
		short bigger = move.y > move.x ? move.y : move.x;
		if (smaller == 1 && bigger == 2)
			return true;
		return false;
	}

	bool Bishop::validMove(const Pos &new_pos, const Pieces *target) const
    {
        (void) target;
		Move move = new_pos - pos;
		if (abs(move.x) == abs(move.y))
			return true;
		return false;
	}

	bool Queen::validMove(const Pos &new_pos, const Pieces *target) const
    {
        (void) target;
		Move move = new_pos - pos;
		info("new pos: ", new_pos);
		info("pos: ", pos);
		info("move: ", move);
		if ((move.x == 0 && move.y != 0) || (move.y == 0 && move.x != 0))
			return true;
		if (abs(move.x) == abs(move.y))
			return true;
		return false;
	}

	bool King::validMove(const Pos &new_pos, const Pieces *target) const
    {
        (void) target;
		Move move = new_pos - pos;
		if (!move.x && !move.y)
			return false;
		if (abs(move.x) <= 1 && abs(move.y) <= 1)
			return true;
		return false;
	}

/* ---------------------------------------------------------------------- Operator Overloads --------------------------------------------------------------------------- */

bool operator==(const std::unique_ptr<Pieces> &piece1, const std::unique_ptr<Pieces> &piece2)
{
	if (piece1->getPosition() == piece2->getPosition() && piece1->getType() == piece2->getType() && piece1->getColor() == piece2->getColor())
		return true;
	return false;
}

bool operator==(const std::unique_ptr<Pieces> &piece1, const Pieces *piece2)
{
	if (piece1->getPosition() == piece2->getPosition() && piece1->getType() == piece2->getType() && piece1->getColor() == piece2->getColor())
		return true;
	return false;
}

bool operator==(const Pieces *piece1, const std::unique_ptr<Pieces> &piece2)
{
	if (piece1->getPosition() == piece2->getPosition() && piece1->getType() == piece2->getType() && piece1->getColor() == piece2->getColor())
		return true;
	return false;
}

std::ostream& operator<<(std::ostream &os, const std::unique_ptr<Pieces> &_piece)
{
	std::string s = _piece->getColor() == BLACK ? "black" : "white";
	os << "color: " << s << std::endl;
	os << "type: " << _piece->getType() << std::endl;
	os << _piece->getPosition() << std::endl;
	return os;
}

std::ostream& operator<<(std::ostream &os, const Pieces *_piece)
{
	os << "color: " << _piece->getColor() << std::endl;
	os << "type: " << _piece->getType() << std::endl;
	os << _piece->getPosition() << std::endl;
	return os;
}
