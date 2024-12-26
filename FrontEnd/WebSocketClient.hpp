#ifndef WEBSOCKETCLIENT_H
#define WEBSOCKETCLIENT_H

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

class WebSocketClient : public QObject {
	Q_OBJECT
private:
	QWebSocket *socket;

public:
	WebSocketClient() : QObject(nullptr){
        socket = nullptr;
    };
	~WebSocketClient() {
		delete socket;
	}
	void connectSock(QString username) {
        if(!socket) {
            delete socket;
            socket = nullptr;
        }
        socket = new QWebSocket();
		connect(socket, &QWebSocket::connected, this, &WebSocketClient::onConnected);
		connect(socket, &QWebSocket::textMessageReceived, this, &WebSocketClient::onMessageReceived);
		connect(socket, &QWebSocket::disconnected, this, &WebSocketClient::onDisconnected);
		QUrl qurl = QUrl("ws://localhost:8000/ws/" + username);
		qDebug() <<  "qurl: " << qurl;
		socket->open(qurl);

		QEventLoop loop;
		connect(socket, &QWebSocket::connected, &loop, [&loop]() {
			qDebug() << "Connected!";
			loop.quit();
		});
		connect(socket, &QWebSocket::errorOccurred, &loop, [&loop](QAbstractSocket::SocketError error) {
			qDebug() << "Error occurred:" << error;
			loop.quit();
		});

		loop.exec();  // Blocks until the connection is established or an error occurs
	}

signals:
	void newPlayerConnection();

public slots:
	void onConnected() {
		qDebug() << "Connected to server";
	}

	void onMessageReceived(QString message) {
		if(message.startsWith("update connections")) {
			qDebug() << "emitting";
			// emit newPlayerConnection();
		}
		qDebug() << "Received message from server:" << message;
	}

	void onDisconnected() {
		qDebug() << "Disconnected from server";
		socket->close();
	}

	void sendMessage(QString message) {
		socket->sendTextMessage(message);
	}
};

inline namespace Global {
extern std::unique_ptr<WebSocketClient> my_ws;
}

#endif
