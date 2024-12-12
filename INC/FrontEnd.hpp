// #include <iostream>
// #include <map>
// #include <vector>
// #include <memory>

// #include "Pieces.hpp"
// #include "Board.hpp"


// class Events
// {
// private:
// 	Board *board;
// 	t_dim *dim;
// 	std::map<int, bool> keys;
// 	void keyEvents(const short key, const bool type, bool &quit);

// public:
// 	Events();
// 	~Events();
// 	void setBoard(Board &_board);
// 	void setDim(t_dim &_dim);
// 	std::map<int, bool> getKeys() const { return keys; };

// 	void eventHandler(const SDL_Event &event, bool &player_turn, bool &quit);
// 	void clickPiece(const short x, const short y, bool &player_turn);
// };

// Events::Events()
// {
// 	// keys[SDLK_w] = false;
// 	// keys[KEY_MY_CTRL] = false;
// }

// Events::~Events()
// {
// }

// void Events::setBoard(Board &_board)
// {
// 	board = &_board;
// }

// void Events::setDim(t_dim &_dim)
// {
// 	dim = &_dim;
// }

// void Events::clickPiece(const short x, const short y, bool &player_turn)
// {
// 	const short square_x = x * 8 / dim->board;
// 	const short square_y = y * 8 / dim->board;
// 	const std::vector<std::unique_ptr<Pieces>> &active_pieces = board->getActivePieces();

// 	for (auto it = active_pieces.cbegin(); it != active_pieces.cend(); it++)
// 	{
// 		const std::unique_ptr<Pieces>::pointer piece = it->get();

// 		Pos pos = piece->getPosition();
// 		short pos_rev_y = pos.reverseY();
// 		if (piece->getColor() == player_turn && pos.x == square_x && pos_rev_y == square_y)
// 		{
// 			switch (piece->getType())
// 			{
// 			case PAWN:
// 				board->setSelectedPiece(std::make_unique<Pawn>(pos.x, pos.y, piece->getColor()));
// 				break;
// 			case ROOK:
// 				board->setSelectedPiece(std::make_unique<Rook>(pos.x, pos.y, piece->getColor()));
// 				break;
// 			case KNIGHT:
// 				board->setSelectedPiece(std::make_unique<Knight>(pos.x, pos.y, piece->getColor()));
// 				break;
// 			case BISHOP:
// 				board->setSelectedPiece(std::make_unique<Bishop>(pos.x, pos.y, piece->getColor()));
// 				break;
// 			case QUEEN:
// 				board->setSelectedPiece(std::make_unique<Queen>(pos.x, pos.y, piece->getColor()));
// 				break;
// 			case KING:
// 				board->setSelectedPiece(std::make_unique<King>(pos.x, pos.y, piece->getColor()));
// 				break;
// 			default:
// 				break;
// 			}
// 			fout("click piece selected piece: ", board->getSelectedPiece());
// 			return;
// 		}
// 	}
// 	board->setSelectedPiece(nullptr);
// }

// void Events::eventHandler(const SDL_Event &e, bool &player_turn, bool &quit)
// {

// 	if (e.type == SDL_KEYDOWN || e.type == SDL_KEYUP)
// 	{
// 		bool type = e.type == SDL_KEYDOWN ? true : false;
// 		keyEvents(e.key.keysym.sym, type, quit);
// 	}
// 	else if (e.type == SDL_QUIT)
// 	{
// 		quit = true;
// 	}
// 	else if (e.type == SDL_MOUSEBUTTONDOWN)
// 	{
// 		if (board->getSelectedPiece() == nullptr)
// 		{
// 			std::string msg = player_turn == BLACK ? "Black" : "White";
// 			fout("Player turn: ", msg);
// 			clickPiece(e.button.x, e.button.y, player_turn);
// 		}
// 		else
// 			board->moveSelectedPiece(e.button.x, e.button.y);
// 	}
// }

// void Events::keyEvents(const short key, const bool type, bool &quit)
// {
// 	if (keys.find(key) == keys.end())
// 		return;
// 	keys[key] = type;
// 	if (keys[KEY_MY_CTRL] == true && keys[SDLK_w] == true)
// 	{
// 		quit = true;
// 	}
// }

// std::ostream &operator<<(std::ostream &os, const Events &events)
// {
// 	std::map<int, bool> temp = events.getKeys();
// 	for (auto it = temp.begin(); it != temp.end(); it++)
// 	{
// 		os << it->first << ": " << it->second << std::endl;
// 	}
// 	return os;
// }
