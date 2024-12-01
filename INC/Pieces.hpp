#include "Board.hpp"

class Pieces
{
protected:
	Pos pos;
	bool color;
	PieceType type;
public:
	
	Pieces() {};
	virtual ~Pieces() {};

	virtual void	init() = 0;
	virtual void	setPosition(Pos new_pos) = 0;
	virtual bool	validMove(Pos new_pos) = 0;
	virtual bool	makeMove(Pos new_pos) = 0;

	Pos getPosition() const { return pos; }
	bool getColor() const { return color; }
	void setColor(bool c) { color = c; }
};

class NoPiece : public Pieces {
public:
	NoPiece();
	~NoPiece();	
}

class Pawn : public Pieces {
public:
	Pawn() {}
	virtual ~Pawn() {}

	void init() override {
		// Initialize the pawn's position based on color
	}

	void setPosition(Pos new_pos) override {
		// Set the pawn's position
	}

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
	Rook() {}
	virtual ~Rook() {}

	void init() override {
		// Initialize the rook's position
	}

	void setPosition(Pos new_pos) override {
		// Set the rook's position
	}

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
	Knight() {}
	virtual ~Knight() {}

	void init() override {
		// Initialize the knight's position
	}

	void setPosition(Pos new_pos) override {
		// Set the knight's position
	}

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
	Bishop() {}
	virtual ~Bishop() {}

	void init() override {
		// Initialize the bishop's position
	}

	void setPosition(Pos new_pos) override {
		// Set the bishop's position
	}

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
	Queen() {}
	virtual ~Queen() {}

	void init() override {
		// Initialize the queen's position
	}

	void setPosition(Pos new_pos) override {
		// Set the queen's position
	}

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
	King() {}
	virtual ~King() {}

	void init() override {
		// Initialize the king's position
	}

	void setPosition(Pos new_pos) override {
		// Set the king's position
	}

	bool validMove(Pos new_pos) override {
		// Check if the move is valid for a king
		return true;
	}

	bool makeMove(Pos new_pos) override {
		// Move the king
		return true;
	}
};

