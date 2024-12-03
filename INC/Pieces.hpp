#pragma once

#include "main.hpp"

class Pieces
{
protected:
	Pos pos;
	bool color;
	PieceType type;
public:
	Pieces(short _x, short _y) : pos(_x, _y) {
		color = pos.x <= 1 ?  WHITE : BLACK;
	};
	virtual ~Pieces() {};

	virtual bool	validMove(Squares square) = 0;
	bool	makeMove(Pos new_pos) {
		pos = new_pos;
	};

	Pos getPosition() const { return pos; }
	bool getColor() const { return color; }
	void setColor(bool c) { color = c; }
};

class Pawn : public Pieces {
public:
	bool		firstMove = true;
	const		PieceType type = PAWN;
	const short	dir = color == BLACK ? -1 : 1;
	Pawn(short _x, short _y) : Pieces(_x, _y) {};
	~Pawn() {}

	bool validMove(Squares square) override {
		Move move = pos - square.pos;

		// first handle special cases
		if ((move.x == 1 || move.x == -1)
			&& square.piece == nullptr
			&& (move.y == 1 * dir));
			return true;
		if(firstMove && move.y == 2 * dir)
			return true;

		// then error cases
		if(move.x != 0 || move.y != dir)
			return false;

		// then it should be true
		return true;
	}
};

class Rook : public Pieces {
public:
	Rook(short _x, short _y) : Pieces(_x, _y) {};
	~Rook() {}

	bool validMove(Squares square) override {
		return true;
	}
};

class Knight : public Pieces {
public:
	Knight(short _x, short _y) : Pieces(_x, _y) {};
	~Knight() {}

	bool validMove(Squares square) override {
		return true;
	}
};

class Bishop : public Pieces {
public:
	Bishop(short _x, short _y) : Pieces(_x, _y) {};
	~Bishop() {}

	bool validMove(Squares square) override {
		return true;
	}
};

class Queen : public Pieces {
public:
	Queen(short _x, short _y) : Pieces(_x, _y) {};
	~Queen() {}

	bool validMove(Squares square) override {
		return true;
	}
};

class King : public Pieces {
public:
	King(short _x, short _y) : Pieces(_x, _y) {};
	~King() {}

	bool validMove(Squares square) override {
		return true;
	}
};
