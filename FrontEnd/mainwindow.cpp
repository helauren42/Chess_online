#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include "online.hpp"

MStackedWidgets::MStackedWidgets() {
	widLogin = new login();
	widSignup = new signup();
	widMenu = new Menu();
	widGame = new Game();
	this->addWidget(widLogin);
	this->addWidget(widSignup);
	this->addWidget(widMenu);
	this->addWidget(widGame);
}

MStackedWidgets::~MStackedWidgets() {
	delete widLogin;
	delete widSignup;
	delete widMenu;
	delete widGame;
}

void	MainWindow::onSigLogin() {
	stackedWidgets->setCurrentWidget(stackedWidgets->widLogin);
	this->setWindowTitle("Login");
}

void	MainWindow::onValidLogin() {
	stackedWidgets->setCurrentWidget(stackedWidgets->widLogin);
	qDebug() << "login succesfull";
	emit this->sigOpenMenu();
}

void	MainWindow::onFaultyLogin(const QString& msg) {
	stackedWidgets->setCurrentWidget(stackedWidgets->widLogin);
    this->stackedWidgets->widLogin->setFaultyState(msg);
	qDebug() << "login failed";
}

void	MainWindow::onSigSignup() {
	stackedWidgets->setCurrentWidget(stackedWidgets->widSignup);
	this->setWindowTitle("Sign up");
	qDebug() << "on sig signup";
}

void MainWindow::onOpenMenu() {
	stackedWidgets->setCurrentWidget(stackedWidgets->widMenu);
	this->setWindowTitle("Menu");
    emit stackedWidgets->widMenu->getOnlinePlayers(); // online object then sends signal with players to updateOnlinePlayers
	qDebug() << "on open menu";
}

void MainWindow::onLaunchGame() {
	qDebug() << "pre launch game widget";
	this->setWindowTitle("Game");
	stackedWidgets->setCurrentWidget(stackedWidgets->widGame);
	qDebug() << "launching game widget";
}

MainWindow::MainWindow(QWidget *parent)
	: QMainWindow(parent)
	, ui(new Ui::MainWindow)
{
	ui->setupUi(this);
	this->setWindowTitle("Login");
	// this->setFixedSize(this->size());

	stackedWidgets = new MStackedWidgets();
	setCentralWidget(stackedWidgets);
	stackedWidgets->setCurrentWidget(stackedWidgets->widLogin);

	// Login
	connect(stackedWidgets->widLogin, &login::sigUpdateLogin, &online, &Online::onUpdateLogin);
	connect(stackedWidgets->widLogin, &login::sigRedirSignup, this, &MainWindow::onSigSignup);
	connect(stackedWidgets->widLogin, &login::sigValidLogin, this, &MainWindow::onValidLogin);
    connect(&online, &Online::sigMakeLogin, this, &MainWindow::onOpenMenu);
    connect(&online, &Online::sigFaultyLogin, this, &MainWindow::onFaultyLogin);

	// Signup
	connect(stackedWidgets->widSignup, &signup::sigRedirLogin, this, &MainWindow::onSigLogin);
    connect(stackedWidgets->widSignup, &signup::sigCreateAccount, &online, &Online::onCreateAccount);

	// Menu
	connect(stackedWidgets->widMenu, &Menu::sigLauchGame, this, &MainWindow::onLaunchGame);
	connect(stackedWidgets->widMenu, &Menu::sigLauchGame, stackedWidgets->widGame, &Game::onStartGame);
    connect(stackedWidgets->widMenu, &Menu::sigLogOut, &online, &Online::onLogout);
	connect(stackedWidgets->widMenu, &Menu::sigLogOut, this, &MainWindow::onSigLogin);
    connect(stackedWidgets->widMenu, &Menu::getOnlinePlayers, &online, &Online::onGetOnlinePlayers);
	
	// Online
    connect(&online, &Online::sigUpdateOnlinePlayers, stackedWidgets->widMenu, &Menu::onUpdateOnlinePlayers);
    connect(&online, &Online::sigSignupState, stackedWidgets->widSignup, &signup::onUpdateState);
    connect(stackedWidgets->widMenu, &Menu::sigSendChallenge, &online, &Online::onSendChallenge);

    // Game
	connect(this, &MainWindow::sigOpenMenu, this, &MainWindow::onOpenMenu);
	// connect(stackedWidgets->widGame, &Game::sigClickedBoard, stackedWidgets->widGame, &Game::onClickBoard);
    }

MainWindow::~MainWindow()
{
	delete ui;
	delete stackedWidgets;
}

