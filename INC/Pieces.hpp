#include "main.hpp"

class Pieces
{
protected:
	Pos pos;
	bool color;
	PieceType type;
public:	
	Pieces(short _x, short _y) : pos(_x, _y) {
	};
	virtual ~Pieces() {};

	virtual bool	validMove(Pos new_pos) = 0;
	virtual bool	makeMove(Pos new_pos) {
		pos = new_pos;
	};

	Pos getPosition() const { return pos; }
	bool getColor() const { return color; }
	void setColor(bool c) { color = c; }
};

class Pawn : public Pieces {
public:
	Pawn(short _x, short _y) : Pieces(_x, _y) {};
	virtual ~Pawn() {}

	bool validMove(Pos new_pos) override {
		// Check if the move is valid for a pawn
		return true;
	}

	bool makeMove(Pos new_pos) override {
		// Move the pawn
		return true;
	}
};

class Rook : public Pieces {
public:
	Rook(short _x, short _y) : Pieces(_x, _y) {};
	virtual ~Rook() {}

	bool validMove(Pos new_pos) override {
		// Check if the move is valid for a rook
		return true;
	}

	bool makeMove(Pos new_pos) override {
		// Move the rook
		return true;
	}
};

class Knight : public Pieces {
public:
	Knight(short _x, short _y) : Pieces(_x, _y) {};
	virtual ~Knight() {}

	bool validMove(Pos new_pos) override {
		// Check if the move is valid for a knight
		return true;
	}

	bool makeMove(Pos new_pos) override {
		// Move the knight
		return true;
	}
};

class Bishop : public Pieces {
public:
	Bishop(short _x, short _y) : Pieces(_x, _y) {};
	virtual ~Bishop() {}

	bool validMove(Pos new_pos) override {
		// Check if the move is valid for a bishop
		return true;
	}

	bool makeMove(Pos new_pos) override {
		// Move the bishop
		return true;
	}
};

class Queen : public Pieces {
public:
	Queen(short _x, short _y) : Pieces(_x, _y) {};
	virtual ~Queen() {}

	bool validMove(Pos new_pos) override {
		// Check if the move is valid for a queen
		return true;
	}

	bool makeMove(Pos new_pos) override {
		// Move the queen
		return true;
	}
};

class King : public Pieces {
public:
	King(short _x, short _y) : Pieces(_x, _y) {};
	virtual ~King() {}

	bool validMove(Pos new_pos) override {
		// Check if the move is valid for a king
		return true;
	}

	bool makeMove(Pos new_pos) override {
		// Move the king
		return true;
	}
};

