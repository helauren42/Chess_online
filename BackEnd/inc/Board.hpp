#ifndef BOARD_HPP
#define BOARD_HPP

#include "Utils.hpp"
#include "Pieces.hpp"
#include <memory>
#include <vector>
#include <array>

struct Cell
{
	PieceType type = NONE;
	bool *color = nullptr;
};

class Board
{
private:
	bool has_en_passant = false;
	bool player_turn = WHITE;
	bool castling = false;
	std::array<std::array<Cell, 8>, 8> cell_board;
	std::unique_ptr<Pieces> selected_piece = nullptr;
	std::vector<std::unique_ptr<Pieces>> active_pieces;
	std::vector<std::unique_ptr<Pieces>> dead_white_pieces;
	std::vector<std::unique_ptr<Pieces>> dead_black_pieces;

	const std::array<Move, 8> king_moves = { Move(1, 2), Move(1, -2), Move(-1, 2), Move(-1, -2), Move(2, 1), Move(2, -1), Move(-2, 1), Move(-2, -1) };


public:
	Board() { init(); };
	~Board() {};

	/* ---------------------------------------------------------------------- initialization  --------------------------------------------------------------------------- */

	std::unique_ptr<Pieces> initPiece(const short &x, const short &y);
	void init();

	/* ---------------------------------------------------------------------- getters and setters  --------------------------------------------------------------------------- */

	void setSelectedPiece(std::unique_ptr<Pieces> piece) { selected_piece = std::move(piece); }
	void setPlayerTurn(bool *_player_turn) { player_turn = _player_turn; }

	const std::vector<std::unique_ptr<Pieces>> &getActivePieces() const { return active_pieces; }
	const std::unique_ptr<Pieces> &getSelectedPiece() const { return selected_piece; }
	const std::array<std::array<Cell, 8>, 8> &getCellBoard() const { return cell_board; }

	void setBoard();
	Pieces *getTargetPiece(const Pos &new_pos) const;
	Pieces *getKing() const;

	/* ---------------------------------------------------------------------- Validating move --------------------------------------------------------------------------- */

	bool foundObstacle(Pos old_pos, Pos new_pos, PieceType type, bool piece_color);
	bool validMove(Pos new_pos, const Pieces *piece, const Pieces *target_piece);
	std::vector<Pos> intersection(const Pos &start, const Pos &end);
	
	/* ---------------------------------------------------------------------- Making the move --------------------------------------------------------------------------- */

    void removePiece(Pieces *piece);
	void makeEnPassant(const Pos &old_pos, const Move &move);
	void moveSelectedPiece(const Pos &new_pos);

	/* ---------------------------------------------------------------------- End game checks --------------------------------------------------------------------------- */

	// add is stalemate
	Pieces *isCheck(const Pieces *target = nullptr);
	bool canUncheck(Pieces *checker);
	bool isCheckmate();
	bool isImmobilized(Pieces *piece);
};

#endif