#pragma once
#include <iostream>
#include "MyCppLib/MyCppLib.hpp"

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

typedef struct s_dim
{
	short window_width = 0;
	short window_height = 0;
	short board = 0;
	short square = 0;
} t_dim;

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
		xyToFr();
	};

	void setPos(std::string _fr)
	{
		file_rank = _fr;
		frToXy();
	};

	int	reverseY() {
		int rev = 0;
		if(y < 4)
			rev = 7 - y;
		else
			rev = abs(y - 7);
		return rev;
	}

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

Pos	coordinatesToPos(const short x, const short y, const short win_width, const short win_height) {
	out("coordinate x: ", x, "coordinate y: ", y);
	Pos pos(x * 8 / win_width, y * 8 / win_height);
	pos.setPos(pos.x, pos.reverseY());
	return pos;
}

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
	os << "rank: " << pos.file_rank << std::endl;
	os << "x: " << pos.x << std::endl;
	os << "y: " << pos.y << std::endl;
	return os;
}

bool operator==(Pos pos1, Pos pos2) {
	return pos1.x == pos2.x && pos1.y == pos2.y;
}