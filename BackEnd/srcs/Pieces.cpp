#include "../inc/Pieces.hpp"

Pieces::Pieces(short _x, short _y, PieceType _type) : pos(_x, _y), type(_type)
{
	color = pos.y <= 1 ? WHITE : BLACK;
}

Pieces::Pieces(short _x, short _y, PieceType _type, bool _color) : pos(_x, _y), color(_color), type(_type) {}

Pieces::~Pieces() {}

PieceType Pieces::getType() const { return type; }
bool Pieces::getFirstMove() const { return firstMove; }
Pos Pieces::getPosition() const { return pos; }
bool Pieces::getColor() const { return color; }

void Pieces::makeMove(const Pos &new_pos)
{
	pos = new_pos;
	firstMove = false;
}

Pawn::Pawn(short _x, short _y) : Pieces(_x, _y, PAWN), dir(color == BLACK ? -1 : 1) {}

Pawn::Pawn(short _x, short _y, bool _color) : Pieces(_x, _y, PAWN, _color), dir(_color == BLACK ? -1 : 1) {}

Pawn::~Pawn() {}

bool Pawn::validMove(const Pos &new_pos, const Pieces *target) const
{
	(void) target;
	Move move = new_pos - pos;

	if ((move.x == 1 || move.x == -1) && target != nullptr && (move.y == 1 * dir))
		return true;
	if (target != nullptr || move.x >= 2)
		return false;

	if (move.x == 0 && firstMove && move.y == 2 * dir)
		return true;

	if (move.x != 0 || move.y != dir)
		return false;

	return true;
}

short Pawn::getDir() const { return dir; }

EnPassant::EnPassant(short _x, short _y, bool _color) : Pieces(_x, _y, ENPASSANT, _color), dir(_color == BLACK ? -1 : 1) {}

EnPassant::~EnPassant() {}

short EnPassant::getDir() const { return dir; }

bool EnPassant::validMove(const Pos &new_pos, const Pieces *target) const
{
	(void) new_pos;
	(void) target;
	return false;
}

Rook::Rook(short _x, short _y) : Pieces(_x, _y, ROOK) {}
Rook::Rook(short _x, short _y, bool _color) : Pieces(_x, _y, ROOK, _color) {}
Rook::~Rook() {}

bool Rook::validMove(const Pos &new_pos, const Pieces *target) const
{
	(void) target;
	Move move = new_pos - pos;
	if ((move.x == 0 && move.y != 0) || (move.y == 0 && move.x != 0))
		return true;
	return false;
}

Knight::Knight(short _x, short _y) : Pieces(_x, _y, KNIGHT) {}
Knight::Knight(short _x, short _y, bool _color) : Pieces(_x, _y, KNIGHT, _color) {}
Knight::~Knight() {}

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

Bishop::Bishop(short _x, short _y) : Pieces(_x, _y, BISHOP) {}
Bishop::Bishop(short _x, short _y, bool _color) : Pieces(_x, _y, BISHOP, _color) {}
Bishop::~Bishop() {}

bool Bishop::validMove(const Pos &new_pos, const Pieces *target) const
{
	(void) target;
	Move move = new_pos - pos;
	if (abs(move.x) == abs(move.y))
		return true;
	return false;
}

Queen::Queen(short _x, short _y) : Pieces(_x, _y, QUEEN) {}
Queen::Queen(short _x, short _y, bool _color) : Pieces(_x, _y, QUEEN, _color) {}
Queen::~Queen() {}

bool Queen::validMove(const Pos &new_pos, const Pieces *target) const
{
	(void) target;
	Move move = new_pos - pos;
	if ((move.x == 0 && move.y != 0) || (move.y == 0 && move.x != 0))
		return true;
	if (abs(move.x) == abs(move.y))
		return true;
	return false;
}

King::King(short _x, short _y) : Pieces(_x, _y, KING) {}
King::King(short _x, short _y, bool _color) : Pieces(_x, _y, KING, _color) {}
King::~King() {}

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
