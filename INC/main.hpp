#include "MyCppLib/MyCppLib.hpp"

// The x-coordinate corresponds to the file (columns), labeled a to h from left to right.
// The y-coordinate corresponds to the rank (rows), numbered 1 to 8 from bottom to top.

using namespace std;

enum PieceType
{
	NOPIECE,
	PAWN,
	ROOK,
	KNIGHT,
	BISHOP,
	QUEEN,
	KING
};

typedef struct Pos
{
	int x;
	int y;
	string file_rank;
};

typedef struct Xy
{
	int x;
	int y;
};

Xy frToXy(const string &s)
{
	Xy xy;
	xy.x = s[0] - 97;
	xy.y = s[1] - 49;
	return xy;
}

string frToXy(const Xy &xy)
{
	string s;
	s[0] = xy.x + 97;
	s[1] = xy.y + 49;
	return s;
}

enum
{
	BLACK,
	WHITE
};
