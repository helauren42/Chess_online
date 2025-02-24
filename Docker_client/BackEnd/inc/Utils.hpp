#ifndef UTILS_HPP
#define UTILS_HPP

#include <iostream>
#include "../MyCppLib/Logger/Logger.hpp"

using namespace Logger;

enum PieceType {
	PAWN,
	ROOK,
	KNIGHT,
	BISHOP,
	QUEEN,
	KING,
	ENPASSANT,
	NONE
};

enum PLAYER_COLOR {
	BLACK,
	WHITE,
	COLOR_NONE,
};

struct Move
{
	short x;
	short y;
	Move();
	Move(const short _x, const short _y);
	~Move();
};

struct Pos
{
public:
	Pos();
	Pos(short _x, short _y);
	void setPos(short _x, short _y);
	void setPos(std::string _fr);
	int reverseY();
	bool isOutOfBounds();
	short x;
	short y;
	std::string file_rank;

private:
	void frToXy();
	void xyToFr();
};

Pos coordinatesToPos(const short x, const short y, const short win_width, const short win_height);

std::ostream& operator<<(std::ostream& os, const Move& move);
Move operator-(Pos new_pos, Pos old_pos);
Pos operator+(Pos pos, Move move);
std::ostream& operator<<(std::ostream& os, const Pos& pos);
bool operator==(const Pos& pos1, const Pos& pos2);
bool operator!=(const Pos& pos1, const Pos& pos2);

#endif // UTILS_HPP
