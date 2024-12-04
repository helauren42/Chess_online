#ifndef PIECES_HPP
#define PIECES_HPP

#include <iostream>
#include <string>
#include <memory>

template <typename T>
using unique_ptr = std::unique_ptr<T>;

enum PieceType {
	PAWN,
	ROOK,
	KNIGHT,
	BISHOP,
	QUEEN,
	KING
};

enum {
	BLACK,
	WHITE
};

struct Move
{
	short x;
	short y;
};

struct Pos
{
public:
	Pos()
	{
		x = 0;
		y = 0;
		xyToFr();
	};
	Pos(short _x, short _y)
	{
		x = _x;
		y = _y;
		xyToFr();
	};
	short x;
	short y;
	std::string file_rank;


	void setPos(short _x, short _y)
	{
		x = _x;
		y = _y;
		if(!validPos())
			throw (std::invalid_argument("Position not valid"));
		xyToFr();
	};

	void setPos(std::string _fr)
	{
		file_rank = _fr;
		frToXy();
	};

	bool validPos() { return x >= 0 && x <= 7 && y >= 0 && y <= 7; }

private:
	void frToXy()
	{
		x = file_rank[0] - 97;
		y = file_rank[1] - 49;
	}
	void xyToFr()
	{
		file_rank[0] = x + 97;
		file_rank[1] = y + 49;
	}
};

Move operator-(Pos new_pos, Pos old_pos)
{
	Move move;
	move.x = new_pos.x - old_pos.x;
	move.y = new_pos.y - old_pos.y;
	return move;
}

Pos operator+(Pos pos, Move move)
{
	pos.setPos(pos.x + move.x, pos.y + move.y);
	return pos;
}

std::ostream& operator<<(std::ostream& os, const Pos& pos) {
	os << pos.file_rank << std::endl;
	os << "x: " << pos.x << std::endl;
	os << "y: " << pos.y << std::endl;
	return os;
}

bool operator==(Pos pos1, Pos pos2) {
	return pos1.x == pos2.x && pos1.y == pos2.y;
}

class Pieces
{
protected:
	Pos pos;
	bool color;
	PieceType type;
	const std::string file;
public:
	Pieces(short _x, short _y, std::string _file) : pos(_x, _y), file(_file) {
		color = pos.x <= 1 ?  WHITE : BLACK;
	};
	virtual ~Pieces() {};

	virtual bool	validMove(const Pos& new_pos, const unique_ptr<Pieces>& piece) = 0;
	virtual void	makeMove(const Pos& new_pos) {
		pos = new_pos;
	};
	PieceType	getType() const { return type; }
	std::string	getImgDir() const { return file; }
	Pos getPosition() const { return pos; }
	bool getColor() const { return color; }
	void setColor(bool c) { color = c; }
};

class Pawn : public Pieces {
public:
	bool		firstMove = true;
	const		PieceType type = PAWN;
	const short	dir = color == BLACK ? -1 : 1;
	
	Pawn(short _x, short _y) : Pieces(_x, _y, color == BLACK ? "../IMG/USE/b_pawn.png" : "../IMG/USE/w_pawn.png") {};
	~Pawn() {}

	bool validMove(const Pos& new_pos, const unique_ptr<Pieces>& piece) override {
		Move move = pos - new_pos;

		// first handle special cases
		if ((move.x == 1 || move.x == -1)
			&& piece != nullptr
			&& (move.y == 1 * dir))
			return true;
		if(firstMove && move.y == 2 * dir)
			return true;

		// then error cases
		if(move.x != 0 || move.y != dir)
			return false;

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
	const		PieceType type = ROOK;
	Rook(short _x, short _y) : Pieces(_x, _y, color == BLACK ? "../IMG/USE/b_rook.png" : "../IMG/USE/w_rook.png") {};
	~Rook() {}

	bool validMove(const Pos& new_pos, const unique_ptr<Pieces>& piece) override {
		return true;
	}
};

class Knight : public Pieces {
public:
	const		PieceType type = KNIGHT;
	Knight(short _x, short _y) : Pieces(_x, _y, color == BLACK ? "../IMG/USE/b_knight.png" : "../IMG/USE/w_knight.png") {};
	~Knight() {}

	bool validMove(const Pos& new_pos, const unique_ptr<Pieces>& piece) override {
		return true;
	}
};

class Bishop : public Pieces {
public:
	const		PieceType type = BISHOP;
	Bishop(short _x, short _y) : Pieces(_x, _y, color == BLACK ? "../IMG/USE/b_bishop.png" : "../IMG/USE/w_bishop.png") {};
	~Bishop() {}

	bool validMove(const Pos& new_pos, const unique_ptr<Pieces>& piece) override {
		return true;
	}
};

class Queen : public Pieces {
public:
	const		PieceType type = QUEEN;
	Queen(short _x, short _y) : Pieces(_x, _y, color == BLACK ? "../IMG/USE/b_queen.png" : "../IMG/USE/w_queen.png") {};
	~Queen() {}

	bool validMove(const Pos& new_pos, const unique_ptr<Pieces>& piece) override {
		return true;
	}
};

class King : public Pieces {
public:
	const		PieceType type = KING;
	King(short _x, short _y) : Pieces(_x, _y, color == BLACK ? "../IMG/USE/b_king.png" : "../IMG/USE/w_king.png") {};
	~King() {}

	bool validMove(const Pos& new_pos, const unique_ptr<Pieces>& piece) override {
		return true;
	}
};



#endif