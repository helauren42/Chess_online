#ifndef PIECES_HPP
#define PIECES_HPP

#include <string>
#include <memory>

#include "Utils.hpp"
#include "../MyCppLib/MyCppLib.hpp"
#include <iostream>

class Pieces
{
protected:
	bool firstMove = true;
	Pos pos;
	bool color;
	const PieceType type;

public:
	Pieces(short _x, short _y, PieceType _type) : pos(_x, _y), type(_type)
	{
		color = pos.y <= 1 ? WHITE : BLACK;
	};
	Pieces(short _x, short _y, PieceType _type, bool _color) : pos(_x, _y), color(_color), type(_type) {};
	virtual ~Pieces() {};

	PieceType getType() const { return type; }
	bool getFirstMove() const { return firstMove; }
	Pos getPosition() const { return pos; }
	bool getColor() const { return color; }

	virtual bool validMove(const Pos &new_pos, const Pieces *target) const = 0;
	void makeMove(const Pos &new_pos)
	{
		pos = new_pos;
		firstMove = false;
	};
};

class Pawn : public Pieces
{
public:
	const short dir = color == BLACK ? -1 : 1;

	Pawn(short _x, short _y) : Pieces(_x, _y, PAWN) {};
	Pawn(short _x, short _y, bool _color) : Pieces(_x, _y, PAWN, _color) {};
	~Pawn() {}

	bool validMove(const Pos &new_pos, const Pieces *target) const override
	{
		Logger::info("new pos: ", new_pos);
		Logger::info("pos: ", pos);
		Move move = new_pos - pos;

		Logger::info("move: ", move);
		// first handle special cases
		if ((move.x == 1 || move.x == -1) && target != nullptr && (move.y == 1 * dir))
		{
			Logger::info("pawn move 1 valid\n");
			return true;
		}
		if (target != nullptr || move.x >= 2)
			return false;

		if (move.x == 0 && firstMove && move.y == 2 * dir)
		{
			Logger::info("pawn move 1 valid\n");
			return true;
		}

		// then main error cases
		if (move.x != 0 || move.y != dir)
		{
			return false;
		}

		Logger::info("pawn move default true\n");
		// then it should be true
		return true;
	}
	short getDir() const
	{
		return dir;
	}
};

class EnPassant : public Pieces
{
public:
	const short dir = color == BLACK ? -1 : 1;

	EnPassant(short _x, short _y, bool _color) : Pieces(_x, _y, ENPASSANT, _color) {};
	~EnPassant() {}
	short getDir() const
	{
		return dir;
	}

private:
	bool validMove(const Pos &new_pos, const Pieces *target) const override
	{
		return false;
	}
};

class Rook : public Pieces
{
public:
	Rook(short _x, short _y) : Pieces(_x, _y, ROOK) {};
	Rook(short _x, short _y, bool _color) : Pieces(_x, _y, ROOK, _color) {};

	~Rook() {}

	bool validMove(const Pos &new_pos, const Pieces *target) const override
	{
		Move move = new_pos - pos;
		if ((move.x == 0 && move.y != 0) || (move.y == 0 && move.x != 0))
			return true;
		return false;
	}
};

class Knight : public Pieces
{
public:
	Knight(short _x, short _y) : Pieces(_x, _y, KNIGHT) {};
	Knight(short _x, short _y, bool _color) : Pieces(_x, _y, KNIGHT, _color) {};
	~Knight() {}

	bool validMove(const Pos &new_pos, const Pieces *target) const override
	{
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
};

class Bishop : public Pieces
{
public:
	Bishop(short _x, short _y) : Pieces(_x, _y, BISHOP) {};
	Bishop(short _x, short _y, bool _color) : Pieces(_x, _y, BISHOP, _color) {};
	~Bishop() {}

	bool validMove(const Pos &new_pos, const Pieces *target) const override
	{
		Move move = new_pos - pos;
		if (abs(move.x) == abs(move.y))
			return true;
		return false;
	}
};

class Queen : public Pieces
{
public:
	Queen(short _x, short _y) : Pieces(_x, _y, QUEEN) {};
	Queen(short _x, short _y, bool _color) : Pieces(_x, _y, QUEEN, _color) {};
	~Queen() {}

	bool validMove(const Pos &new_pos, const Pieces *target) const override
	{
		Move move = new_pos - pos;
		Logger::info("new pos: ", new_pos);
		Logger::info("pos: ", pos);
		Logger::info("move: ", move);
		if ((move.x == 0 && move.y != 0) || (move.y == 0 && move.x != 0))
			return true;
		if (abs(move.x) == abs(move.y))
			return true;
		return false;
	}
};

class King : public Pieces
{
public:
	King(short _x, short _y) : Pieces(_x, _y, KING) {};
	King(short _x, short _y, bool _color) : Pieces(_x, _y, KING, _color) {};
	~King() {}

	bool validMove(const Pos &new_pos, const Pieces *target) const override
	{
		Move move = new_pos - pos;
		if (!move.x && !move.y)
			return false;
		if (abs(move.x) <= 1 && abs(move.y) <= 1)
			return true;
		return false;
	}
};

bool operator==(const std::unique_ptr<Pieces> &piece1, const std::unique_ptr<Pieces> &piece2)
{
	if (piece1->getPosition() == piece2->getPosition() && piece1->getType() == piece2->getType() && piece1->getColor() == piece2->getColor())
	{
		return true;
	}
	return false;
}

bool operator==(const std::unique_ptr<Pieces> &piece1, const Pieces *piece2)
{
	if (piece1->getPosition() == piece2->getPosition() && piece1->getType() == piece2->getType() && piece1->getColor() == piece2->getColor())
	{
		return true;
	}
	return false;
}

bool operator==(const Pieces *piece1, const std::unique_ptr<Pieces> &piece2)
{
	if (piece1->getPosition() == piece2->getPosition() && piece1->getType() == piece2->getType() && piece1->getColor() == piece2->getColor())
	{
		return true;
	}
	return false;
}

std::ostream &operator<<(std::ostream &os, const std::unique_ptr<Pieces> &_piece)
{
	std::string s = _piece->getColor() == BLACK ? "black" : "white";
	os << "color: " << s << std::endl;
	os << "type: " << _piece->getType() << std::endl;
	os << _piece->getPosition() << std::endl;
	return os;
}

std::ostream &operator<<(std::ostream &os, const Pieces *_piece)
{
	os << "color: " << _piece->getColor() << std::endl;
	os << "type: " << _piece->getType() << std::endl;
	os << _piece->getPosition() << std::endl;
	return os;
}

#endif
