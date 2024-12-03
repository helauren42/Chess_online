#pragma once

#include "MyCppLib/MyCppLib.hpp"
#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>

#include "events.hpp"

// The x-coordinate corresponds to the file (columns), labeled a to h from left to right.
// The y-coordinate corresponds to the rank (rows), numbered 1 to 8 from bottom to top.

using namespace std;

typedef struct s_imgs {
	
}	t_imgs;

typedef struct s_dim {
	int window;
	int board;
	int square;
} t_dim;

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
	string file_rank;

	void setPos(short _x, short _y)
	{
		x = _x;
		y = _y;
		if(!validPos())
			throw (std::invalid_argument("Position not valid"));
		xyToFr();
	};


	void setPos(string _fr)
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
	os << pos.file_rank << endl;
	os << "x: " << pos.x << endl;
	os << "y: " << pos.y << endl;
	return os;
}

bool operator==(Pos pos1, Pos pos2) {
	return pos1.x == pos2.x && pos1.y == pos2.y;
}
