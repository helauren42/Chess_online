#ifndef PIECES_HPP
#define PIECES_HPP

#include <string>
#include <memory>
#include "Utils.hpp"
#include <iostream>

class Pieces
{
protected:
	bool firstMove = true;
	Pos pos;
	bool color;
	const PieceType type;

public:
	Pieces(short _x, short _y, PieceType _type);
	Pieces(short _x, short _y, PieceType _type, bool _color);
	virtual ~Pieces();

	PieceType getType() const;
	bool getFirstMove() const;
	Pos getPosition() const;
	bool getColor() const;

	virtual bool validMove(const Pos &new_pos, const Pieces *target) const = 0;
	void makeMove(const Pos &new_pos);
};

class Pawn : public Pieces
{
public:
	const short dir;

	Pawn(short _x, short _y);
	Pawn(short _x, short _y, bool _color);
	~Pawn();

	bool validMove(const Pos &new_pos, const Pieces *target) const override;
	short getDir() const;
};

class EnPassant : public Pieces
{
public:
	const short dir;

	EnPassant(short _x, short _y, bool _color);
	~EnPassant();
	short getDir() const;

private:
	bool validMove(const Pos &new_pos, const Pieces *target) const override;
};

class Rook : public Pieces
{
public:
	Rook(short _x, short _y);
	Rook(short _x, short _y, bool _color);
	~Rook();

	bool validMove(const Pos &new_pos, const Pieces *target) const override;
};

class Knight : public Pieces
{
public:
	Knight(short _x, short _y);
	Knight(short _x, short _y, bool _color);
	~Knight();

	bool validMove(const Pos &new_pos, const Pieces *target) const override;
};

class Bishop : public Pieces
{
public:
	Bishop(short _x, short _y);
	Bishop(short _x, short _y, bool _color);
	~Bishop();

	bool validMove(const Pos &new_pos, const Pieces *target) const override;
};

class Queen : public Pieces
{
public:
	Queen(short _x, short _y);
	Queen(short _x, short _y, bool _color);
	~Queen();

	bool validMove(const Pos &new_pos, const Pieces *target) const override;
};

class King : public Pieces
{
public:
	King(short _x, short _y);
	King(short _x, short _y, bool _color);
	~King();

	bool validMove(const Pos &new_pos, const Pieces *target) const override;
};

bool operator==(const std::unique_ptr<Pieces> &piece1, const std::unique_ptr<Pieces> &piece2);
bool operator==(const std::unique_ptr<Pieces> &piece1, const Pieces *piece2);
bool operator==(const Pieces *piece1, const std::unique_ptr<Pieces> &piece2);
std::ostream& operator<<(std::ostream &os, const std::unique_ptr<Pieces> &_piece);
std::ostream& operator<<(std::ostream &os, const Pieces *_piece);

#endif
