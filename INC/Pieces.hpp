#include "main.hpp"

class Pieces
{
protected:
	Pos pos;
	bool color;
	PieceType type;
public:
	Pieces(short _x, short _y) : pos(_x, _y) {
		color = pos.x <= 1 ? BLACK : WHITE;
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
	const PieceType type = PAWN;
	Pawn(short _x, short _y) : Pieces(_x, _y) {};
	~Pawn() {}

	bool validMove(Pos new_pos) override {
		Move move = pos - new_pos;
		return true;
	}

	bool makeMove(Pos new_pos) override {
		return true;
	}
};

class Rook : public Pieces {
public:
	Rook(short _x, short _y) : Pieces(_x, _y) {};
	~Rook() {}

	bool validMove(Pos new_pos) override {
		return true;
	}

	bool makeMove(Pos new_pos) override {
		return true;
	}
};

class Knight : public Pieces {
public:
	Knight(short _x, short _y) : Pieces(_x, _y) {};
	~Knight() {}

	bool validMove(Pos new_pos) override {
		Move move = pos - new_pos;
		return true;
	}

	bool makeMove(Pos new_pos) override {
		return true;
	}
};

class Bishop : public Pieces {
public:
	Bishop(short _x, short _y) : Pieces(_x, _y) {};
	~Bishop() {}

	bool validMove(Pos new_pos) override {
		return true;
	}

	bool makeMove(Pos new_pos) override {
		return true;
	}
};

class Queen : public Pieces {
public:
	Queen(short _x, short _y) : Pieces(_x, _y) {};
	~Queen() {}

	bool validMove(Pos new_pos) override {
		return true;
	}

	bool makeMove(Pos new_pos) override {
		return true;
	}
};

class King : public Pieces {
public:
	King(short _x, short _y) : Pieces(_x, _y) {};
	~King() {}

	bool validMove(Pos new_pos) override {
		return true;
	}

	bool makeMove(Pos new_pos) override {
		return true;
	}
};

