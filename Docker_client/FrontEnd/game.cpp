#include "game.hpp"
#include "ui_game.h"

void Game::MakeChessBoard() {
	qDebug() << "MakeChessBoard()";
	qDebug() << "square len: " << square_len;

	if (squares.empty()) {
		for (int row = 0; row < 8; row++) {
			for (int col = 0; col < 8; col++) {
				QLabel* square = new QLabel(this);
				squares.push_back(square);
			}
		}
	}

	const Pieces* red_piece = board->getSelectedPiece().get();

	for (int row = 0; row < 8; row++) {
		for (int col = 0; col < 8; col++) {
			QLabel* square = squares[row * 8 + col];
			square->setGeometry(start_x + col * square_len, row * square_len, square_len, square_len);
			if(red_piece == nullptr) {
				if ((row + col) % 2 == 0) {
					square->setPixmap(lightSquare.scaled(square_len, square_len, Qt::KeepAspectRatio));
				} else {
					square->setPixmap(darkSquare.scaled(square_len, square_len, Qt::KeepAspectRatio));
				}
			}
			else if(red_piece && red_piece->getPosition().x == col && red_piece->getPosition().reverseY() == row) {
				square->setPixmap(redSquare.scaled(square_len, square_len, Qt::KeepAspectRatio));
				Out::stdOut("here3");
			}
		}
	}
}

unsigned int Game::count_pieces() const {
	board->setBoard();
	auto cells = board->getCellBoard();
	unsigned int count = 0;
	for (int y = 0; y < 8 ; y++) {
		for (int x = 0; x < 8 ; x++) {
			if(cells[y][x].type != NONE && cells[y][x].type != ENPASSANT){
				count++;
			}
		}
	}
	return count;
}

void Game::MakePieces() {
	unsigned int num_pieces = count_pieces();
	qDebug() << "MakePieces()";
	qDebug() << "number of pieces: " << num_pieces;

	while(square_pieces.size() < num_pieces) {
		square_pieces.push_back(std::make_unique<QLabel>(this));
	}
	while(square_pieces.size() > num_pieces) {
		square_pieces.pop_back();
	}

	int i = 0;
	auto cells = board->getCellBoard();
	int msc = square_len / 7;
	for (int row = 0; row < 8; row++) {
		for (int col = 0; col < 8; col++) {
			Pos pos(col, row);
			pos.y = pos.reverseY();
			auto cell = cells[row][col];
			if(cell.type == NONE || cell.type == ENPASSANT)
				continue;
			int center = 0;
			if(cell.type == ROOK)
				center = msc * 55 / 100;
			else if(cell.type == PAWN)
				center = msc * 8 / 10;
			QLabel* square = square_pieces[i++].get();
			square->setGeometry(start_x + pos.x * square_len + msc / 2 + center, pos.y * square_len + msc / 2, square_len - msc, square_len - msc);
			square->setPixmap(images.at(std::make_pair(cell.type, cell.color)).scaled(square_len - msc, square_len - msc, Qt::KeepAspectRatio));
			square->show();
		}
	}
}

void Game::computeDim() {
	this->board_len = this->_height;
	this->square_len = board_len / 8;
	this->start_x = (this->_width - this->board_len) / 2;
}

void Game::resizeEvent(QResizeEvent* event) {
	QWidget::resizeEvent(event);  // Call base class implementation

	QSize newSize = event->size();
	this->_width = newSize.width();
	this->_height = newSize.height();

	computeDim();
	MakeChessBoard();
	MakePieces();
	qDebug() << "Window resized to width: " << this->_width << "height: " << this->_height;
}

void Game::emptySquares() {
	for(auto it = squares.rbegin(); it != squares.rend(); it++) {
		(*it)->deleteLater();
	}
	squares.clear();
}

void Game::onStartGame() {
    MakeChessBoard();
    MakePieces();
}

void Game::setHotseatBoard() {
    qDebug() << "set hotseat board";
    if(!this->hotseat_board) {
        qDebug() << "new board:";
        this->hotseat_board = std::make_unique<Board>();
    }
    this->board = this->hotseat_board.get();
}

void Game::on_Restart_clicked()
{
    qDebug() << "On restart clicked";
    this->hotseat_board.release();
    this->hotseat_board = nullptr;
    this->hotseat_board = std::make_unique<Board>();
    this->board = this->hotseat_board.get();
    this->onStartGame();
}

void Game::setOnlineBoard() {
    if(this->online_board)
        this->online_board.release();
    this->online_board = std::make_unique<Board>();
    this->board = this->online_board.get();
}

Game::Game(QWidget *parent)
	: QWidget(parent)
	, ui(new Ui::Game)
{
	ui->setupUi(this);

	this->_height = this->height();
	this->_width = this->width();
	computeDim();

	// lightSquare = QPixmap("../../../IMG/USE/square_brown_light.png");
	// darkSquare = QPixmap("../../../IMG/USE/square_brown_dark.png");
	// redSquare = QPixmap("../../../IMG/USE/square_red.png");
	lightSquare = QPixmap("./IMG/USE/square_brown_light.png");
	darkSquare = QPixmap("./IMG/USE/square_brown_dark.png");
	redSquare = QPixmap("./IMG/USE/square_red.png");
}

Game::~Game()
{
	delete ui;
	emptySquares();
}

void Game::on_MenuButton_clicked()
{
    qDebug("on menu button clicked");
    if(session.game_info.mode != GAMEMODE::ONLINE) {
        emit this->sigRedirMenu();
        return;
    }
    QMessageBox *msgBox = new QMessageBox(this);
    msgBox->setWindowTitle("Leave Game");
    msgBox->setText(QString("Are you sure you want to leave the game? You will lose by forfeit"));
    QPushButton *leaveButton = msgBox->addButton("Yes", QMessageBox::AcceptRole);

	connect(leaveButton, &QPushButton::released, msgBox, &QMessageBox::deleteLater);
    connect(leaveButton, &QPushButton::released, this, &Game::onLeaveGame);

    msgBox->exec();
}
