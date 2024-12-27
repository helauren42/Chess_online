#ifndef COMMON_H
#define COMMON_H

#include <QMainWindow>
#include <QStackedWidget>
#include <QApplication>
#include <QMessageBox>
#include <QScreen>
#include <QWindow>
#include <QWidget>
#include <QDate>
#include <QWebSocket>
#include <QString>
#include <QDebug>

#include <Poco/Net/HTTPClientSession.h>
#include <Poco/Net/HTTPMessage.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/URI.h>

#include <strings.h>

enum GameMode {
	HOTSEAT,
	AI,
	ONLINE,
	OFF
};

struct t_dim {
	short board;
	short x_mid;

	~t_dim() {}
};

#endif
