#ifndef PIECES_HPP
#define PIECES_HPP

#include <string>
#include <memory>

#include "Utils.hpp"
#include "MyCppLib/MyCppLib.hpp"
#include <iostream>

class Pieces
{
protected:
	Pos pos;
	bool color;
	const PieceType type;
public:
	Pieces(short _x, short _y, PieceType _type) : pos(_x, _y), type(_type) {
		color = pos.y <= 1 ?  WHITE : BLACK;
	};
	Pieces(short _x, short _y, PieceType _type, bool _color) : pos(_x, _y), color(_color), type(_type) {
	};
	virtual ~Pieces() {};

	PieceType	getType() const { return type; }
	Pos getPosition() const { return pos; }
	bool getColor() const { return color; }

	virtual bool	validMove(const Pos& new_pos, const Pieces* target) const = 0;
	virtual void	makeMove(const Pos& new_pos) {
		pos = new_pos;
	};
};

class Pawn : public Pieces {
public:
	bool		firstMove = true;
	const short	dir = color == BLACK ? -1 : 1;
	
	Pawn(short _x, short _y) : Pieces(_x, _y, PAWN) {};
	Pawn(short _x, short _y, bool _color) : Pieces(_x, _y, PAWN, _color) {};
	~Pawn() {}

	bool validMove(const Pos& new_pos, const Pieces* target) const override {
		Move move = new_pos - pos;

		// first handle special cases
		if ((move.x == 1 || move.x == -1)
		&& target != nullptr
		&& (move.y == 1 * dir)) {
				return  true;
		}
		if(target)
			return false;
		if(firstMove && move.y == 2 * dir)
			return true;

		// then error cases
		if(move.x != 0 || move.y != dir) {
			return false;
		}

		// then it should be true
		return true;
	}
	void	makeMove(const Pos& new_pos) override {
		pos = new_pos;
		firstMove = false;
	}
};

class Rook : public Pieces {
public:
	Rook(short _x, short _y) : Pieces(_x, _y, ROOK) {};
	Rook(short _x, short _y, bool _color) : Pieces(_x, _y, ROOK, _color) {};

	~Rook() {}

	bool validMove(const Pos& new_pos, const Pieces* target) const override {
		Move move = new_pos - pos;
		if((move.x == 0 && move.y != 0) || (move.y == 0 && move.x != 0))
			return true;
		return false;
	}
};

class Knight : public Pieces {
public:
	Knight(short _x, short _y) : Pieces(_x, _y, KNIGHT) {};
	Knight(short _x, short _y, bool _color) : Pieces(_x, _y, KNIGHT, _color) {};
	~Knight() {}

	bool validMove(const Pos& new_pos, const Pieces* target) const override {
		Move move = new_pos - pos;
		move.x = abs(move.x);
		move.y = abs(move.y);
		if(move.x == move.y)
			return false;
		short smaller = move.x < move.y ? move.x : move.y;
		short bigger = move.y > move.x ? move.y : move.x;
		if(smaller == 1 && bigger == 2)
			return true;
		return false;
	}
};

class Bishop : public Pieces {
public:
	Bishop(short _x, short _y) : Pieces(_x, _y, BISHOP) {};
	Bishop(short _x, short _y, bool _color) : Pieces(_x, _y, BISHOP, _color) {};
	~Bishop() {}

	bool validMove(const Pos& new_pos, const Pieces* target) const override {
		Move move = new_pos - pos;
		if(abs(move.x) == abs(move.y))
			return true;
		return false;
	}
};

class Queen : public Pieces {
public:
	Queen(short _x, short _y) : Pieces(_x, _y, QUEEN) {};
	Queen(short _x, short _y, bool _color) : Pieces(_x, _y, QUEEN, _color) {};
	~Queen() {}

	bool validMove(const Pos& new_pos, const Pieces* target) const override {
		Move move = new_pos - pos;
		if((move.x == 0 && move.y != 0) || (move.y == 0 && move.x != 0))
			return true;
		if(abs(move.x) == abs(move.y))
			return true;
		return false;
	}
};

class King : public Pieces {
public:
	King(short _x, short _y) : Pieces(_x, _y, KING) {};
	King(short _x, short _y, bool _color) : Pieces(_x, _y, KING, _color) {};
	~King() {}

	bool validMove(const Pos& new_pos, const Pieces* target) const override {
		Move move = new_pos - pos;
		if(!move.x && !move.y)
			return false;
		out(move.x, move.y);
		if(abs(move.x) <= 1 && abs(move.y) <= 1)
			return true;
		return false;
	}
};

bool operator==(const std::unique_ptr<Pieces>& piece1, const std::unique_ptr<Pieces>& piece2) {
	if(piece1->getPosition() == piece2->getPosition()
		&& piece1->getType() == piece2->getType()
		&& piece1->getColor() == piece2->getColor()) {
			return true;
		}
	return false;
}

bool operator==(const std::unique_ptr<Pieces>& piece1, const Pieces* piece2) {
	if(piece1->getPosition() == piece2->getPosition()
		&& piece1->getType() == piece2->getType()
		&& piece1->getColor() == piece2->getColor()) {
			return true;
		}
	return false;
}

bool operator==(const Pieces* piece1, const std::unique_ptr<Pieces>& piece2) {
	if(piece1->getPosition() == piece2->getPosition()
		&& piece1->getType() == piece2->getType()
		&& piece1->getColor() == piece2->getColor()) {
			return true;
		}
	return false;
}

std::ostream& operator<<(std::ostream&os, const std::unique_ptr<Pieces>& _piece) {
	std::string s = _piece->getColor() == BLACK ? "black" : "white";
	os << "color: " << s << std::endl;
	os << "type: " << _piece->getType() << std::endl;
	os << _piece->getPosition() << std::endl;
	return os;
}

std::ostream& operator<<(std::ostream&os, const Pieces* _piece) {
	os << "color: " << _piece->getColor() << std::endl;
	os << "type: " << _piece->getType() << std::endl;
	os << _piece->getPosition() << std::endl;
	return os;
}

#endif
