#include "../inc/Utils.hpp"

Move::Move() : x(0), y(0) {}

Move::Move(const short _x, const short _y) : x(_x), y(_y) {}

Move::~Move() {}

Pos::Pos() : x(0), y(0) {
	xyToFr();
}

Pos::Pos(short _x, short _y) : x(_x), y(_y) {
	xyToFr();
}

void Pos::setPos(short _x, short _y) {
	x = _x;
	y = _y;
	xyToFr();
}

void Pos::setPos(std::string _fr) {
	file_rank = _fr;
	frToXy();
}

int Pos::reverseY() {
	int rev = 0;
	if (y < 4)
		rev = 7 - y;
	else
		rev = abs(y - 7);
	return rev;
}

bool Pos::isOutOfBounds() {
	return !(x >= 0 && x <= 7 && y >= 0 && y <= 7);
}

void Pos::frToXy() {
	x = file_rank[0] - 97;
	y = file_rank[1] - 49;
}

void Pos::xyToFr() {
	file_rank[0] = x + 97;
	file_rank[1] = y + 49;
}

Pos coordinatesToPos(const short x, const short y, const short win_width, const short win_height) {
	Pos pos(x * 8 / win_width, y * 8 / win_height);
	pos.setPos(pos.x, pos.reverseY());
	return pos;
}

std::ostream& operator<<(std::ostream& os, const Move& move) {
	os << "x: " << move.x << std::endl;
	os << "y: " << move.y << std::endl;
	return os;
}

Move operator-(Pos new_pos, Pos old_pos) {
	Move move;
	move.x = new_pos.x - old_pos.x;
	move.y = new_pos.y - old_pos.y;
	return move;
}

Pos operator+(Pos pos, Move move) {
	pos.setPos(pos.x + move.x, pos.y + move.y);
	return pos;
}

std::ostream& operator<<(std::ostream& os, const Pos& pos) {
	os << "rank: " << pos.file_rank << std::endl;
	os << "x: " << pos.x << std::endl;
	os << "y: " << pos.y << std::endl;
	return os;
}

bool operator==(const Pos& pos1, const Pos& pos2) {
	return pos1.x == pos2.x && pos1.y == pos2.y;
}

bool operator!=(const Pos& pos1, const Pos& pos2) {
	return pos1.x != pos2.x || pos1.y != pos2.y;
}
