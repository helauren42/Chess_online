#include "MyCppLib/MyCppLib.hpp"

// The x-coordinate corresponds to the file (columns), labeled a to h from left to right.
// The y-coordinate corresponds to the rank (rows), numbered 1 to 8 from bottom to top.

using namespace std;

enum PieceType
{
	PAWN,
	ROOK,
	KNIGHT,
	BISHOP,
	QUEEN,
	KING
};

struct Move {
	short x;
	short y;
};

struct Pos
{
	Pos(short _x, short _y) { x = _x; y = _y; xyToFr();};
	short x;
	short y;
	string file_rank;

	void setPos(short _x, short _y) { x = _x; y = _y; xyToFr();};
	void setPos(string _fr) { file_rank = _fr; frToXy();};

	void frToXy() {
		x = file_rank[0] - 97;
		y = file_rank[1] - 49;
	}
	void xyToFr() {
		file_rank[0] = x + 97;
		file_rank[1] = y + 49;
	}
};

Move getMove(Pos old_pos, Pos new_pos) {
	Move move;
	move.x = new_pos.x - old_pos.x;
	move.y = new_pos.y - old_pos.y;
	return move;
}

enum
{
	BLACK,
	WHITE
};
