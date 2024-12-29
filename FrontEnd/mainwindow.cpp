#include "mainwindow.hpp"
#include "ui_mainwindow.h"
#include "session.hpp"
#include <QPushButton>

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
	session.game_info.reset();
	stackedWidgets->setCurrentWidget(stackedWidgets->widMenu);
	this->setWindowTitle("Menu");
	emit stackedWidgets->widMenu->getOnlinePlayers(); // session object then sends signal with players to updateOnlinePlayers
	qDebug() << "on open menu";
}

void MainWindow::onLaunchGame() {
	qDebug() << "pre launch game widget";
	this->setWindowTitle("Game");
	stackedWidgets->setCurrentWidget(stackedWidgets->widGame);
	qDebug() << "launching game widget";
}

void MainWindow::onLaunchOnlineGame() {
	qDebug() << "pre launch session game vs " << session.game_info.opponent.c_str();
	session.game_info = session.game_info_temp;
	this->setWindowTitle(QString("Vs ") + session.game_info.opponent.c_str());
	stackedWidgets->setCurrentWidget(stackedWidgets->widGame);

	qDebug() << "pre launching session game widget";
}

void MainWindow::onInviteAccept() {
	qDebug() << "on invite accept";

	QJsonObject json;
	json["type"] = "invite answer";
	json["answer"] = "accept";
	json["challenger"] = session.game_info.opponent.c_str();
	json["challenged"] = session.account.username.c_str();
	json["color"] = session.game_info.color;

	QJsonDocument doc(json);
	QString jsonString = doc.toJson();
	session.sendMessage(jsonString);
	session.sigLaunchOnlineGame();
}

void MainWindow::onInviteReject() {
	QJsonObject json;
	json["type"] = "invite answer";
	json["answer"] = "reject";

	QJsonDocument doc(json);
	QString jsonString = doc.toJson();
	session.sendMessage(jsonString);
}

void MainWindow::onInvite() {
	QMessageBox* msgBox = new QMessageBox(this);
	msgBox->setWindowTitle("Invitation");
	msgBox->setText(session.game_info.opponent.c_str() + QString(" has invited you to a game"));

	QPushButton *acceptButton = msgBox->addButton("Accept", QMessageBox::AcceptRole);
	QPushButton *rejectButton = msgBox->addButton("Decline", QMessageBox::RejectRole);

	connect(acceptButton, &QPushButton::released, this, &MainWindow::onInviteAccept);
	connect(rejectButton, &QPushButton::released, this, &MainWindow::onInviteReject);

	connect(acceptButton, &QPushButton::released, msgBox, &QMessageBox::deleteLater);
	connect(rejectButton, &QPushButton::released, msgBox, &QMessageBox::deleteLater);

	msgBox->show();
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
	connect(stackedWidgets->widLogin, &login::sigUpdateLogin, &session, &SessionManager::onUpdateLogin);
	connect(stackedWidgets->widLogin, &login::sigRedirSignup, this, &MainWindow::onSigSignup);
	connect(stackedWidgets->widLogin, &login::sigValidLogin, this, &MainWindow::onValidLogin);
	connect(&session, &SessionManager::sigMakeLogin, this, &MainWindow::onOpenMenu);
	connect(&session, &SessionManager::sigFaultyLogin, this, &MainWindow::onFaultyLogin);

	// Signup
	connect(stackedWidgets->widSignup, &signup::sigRedirLogin, this, &MainWindow::onSigLogin);
	connect(stackedWidgets->widSignup, &signup::sigCreateAccount, &session, &SessionManager::onCreateAccount);

	// Menu
	connect(stackedWidgets->widMenu, &Menu::sigLogOut, &session, &SessionManager::onLogout);
	connect(stackedWidgets->widMenu, &Menu::sigLogOut, this, &MainWindow::onSigLogin);
	connect(stackedWidgets->widMenu, &Menu::getOnlinePlayers, &session, &SessionManager::onGetOnlinePlayers);
	connect(&session, &SessionManager::sigGetOnlinePlayers, &session, &SessionManager::onGetOnlinePlayers);

	// SessionManager
	connect(&session, &SessionManager::sigUpdateOnlinePlayers, stackedWidgets->widMenu, &Menu::onUpdateOnlinePlayers);
	connect(&session, &SessionManager::sigSignupState, stackedWidgets->widSignup, &signup::onUpdateState);
	connect(stackedWidgets->widMenu, &Menu::sigSendChallenge, &session, &SessionManager::onSendChallenge);
	connect(&session, &SessionManager::sigInvite, this, &MainWindow::onInvite);

	// Game
	connect(this, &MainWindow::sigOpenMenu, this, &MainWindow::onOpenMenu);
	connect(stackedWidgets->widMenu, &Menu::sigLauchGame, this, &MainWindow::onLaunchGame);
	connect(stackedWidgets->widMenu, &Menu::sigLauchGame, stackedWidgets->widGame, &Game::onStartGame);
	connect(&session, &SessionManager::sigLaunchOnlineGame, this, &MainWindow::onLaunchOnlineGame);
	connect(&session, &SessionManager::sigLaunchOnlineGame, stackedWidgets->widGame, &Game::onStartGame);
	// connect(stackedWidgets->widGame, &Game::sigClickedBoard, stackedWidgets->widGame, &Game::onClickBoard);
	}

MainWindow::~MainWindow()
{
	delete ui;
	delete stackedWidgets;
}

