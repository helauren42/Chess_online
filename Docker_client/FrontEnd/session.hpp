#ifndef ONLINE_H
#define ONLINE_H

#include "common.hpp"

#include <QMainWindow>
#include <QStackedWidget>
#include <QApplication>
#include <QScreen>
#include <QWindow>
#include <QWidget>
#include <QDate>
#include <QWebSocket>
#include <QString>
#include <QDebug>
#include <QJsonObject>
#include <QJsonDocument>
#include <QMessageBox>

#include <Poco/Net/HTTPClientSession.h>
#include <Poco/Net/HTTPMessage.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/URI.h>

#include <nlohmann/json.hpp>

#include <strings.h>
#include <iostream>
#include <sstream>

using namespace Poco::Net;
using namespace Poco;
using namespace std;

#define MY_URI "http://127.0.0.1:8000"
#define PORT 8000

class SessionManager : public QObject{
	Q_OBJECT
private:
	URI uri;
	HTTPClientSession session;
	HTTPRequest request;
    HTTPResponse response;
	QWebSocket *socket = nullptr;
    QWebSocket *socket_game = nullptr;

signals:

	void    sigPlayerConnection();
	void    sigUpdateOnlinePlayers(const QString& text);
	void    sigSignupState(QString msg);
	void	sigMakeLogin();
	void	sigFaultyLogin(const QString& msg);
	void	sigInvite();
	void	sigLaunchOnlineGame();
    void    sigHandleClick(const Pos& clicked_square);
    void    sigOpponentDisconnection();

public slots:

// Websockets

	void onNewPlayerConnection() {
		emit sigPlayerConnection();
	};

	void onConnected() {
		qDebug() << "Connected to server";
	}

	void onMessageReceived(QString message) {
        qDebug() << "received message: " << message;

		try {
			nlohmann::json jsonObject = nlohmann::json::parse(message.toStdString());
			if(jsonObject["type"] == "challenge") {
				std::string opponent = jsonObject["from"];
				bool color = jsonObject["color"] == "white" ? PLAYER_COLOR::WHITE : PLAYER_COLOR::BLACK;
				game_info_temp.set(GAMEMODE::ONLINE, opponent, this->account.username, opponent, color);
				emit sigInvite();
			}
			if(jsonObject["type"] == "start online game") {
				std::string opponent = jsonObject["opponent"];
				bool color = jsonObject["color"] == "white" ? PLAYER_COLOR::WHITE : PLAYER_COLOR::BLACK;
				game_info_temp.set(GAMEMODE::ONLINE, this->account.username, opponent, opponent, color);
				emit sigLaunchOnlineGame();
			}
			if(jsonObject["type"] == "login") {
                std::string status = jsonObject["status"];
                if(status == "success") {
					emit this->sigMakeLogin();
				}
				else
                    emit this->sigFaultyLogin(status.c_str());
			}
			if(jsonObject["type"] == "update online players") {
                std::map<int, std::string> players;
                std::string text;
                for (auto& item : jsonObject["online_players"].items()) {
                    std::string player = item.value();
                    if(this->account.username != player) {
                        text += player + "\n";
                    }
                }
                emit this->sigUpdateOnlinePlayers(text.c_str());
			}
		}
		catch (...) {
			qDebug() << "message received not json format";
		}
		qDebug() << "Received message from server:" << message;
	}

	void onDisconnected() const {
		qDebug() << "Disconnected from server";
		socket->close();
	}

	void onSendChallenge(const QString& challenger, const QString& challenged) {
		qDebug() << "on send challenge";
		QJsonObject json;
		json["type"] = "challenge";
		json["challenger"] = challenger;
		json["challenged"] = challenged;

		QJsonDocument doc(json);
		QString jsonString = doc.toJson();
		sendMessage(jsonString);
	}

    void gameConnected() {
        qDebug() << "Connected to game port";
    }

    void gameMessageReceived(const QString& message) {
        try {
            QJsonDocument doc = QJsonDocument::fromJson(message.toUtf8());

            QJsonObject jsonObject = doc.object();
            if (jsonObject["type"].toString() == "make click") {
                QString xc = jsonObject["x"].toString();
                QString yc = jsonObject["y"].toString();
                int x = xc.toInt();
                int y = yc.toInt();
                qDebug() << "x: " << x;
                qDebug() << "y: " << y;
                Pos clicked_square(x, y);
                qDebug() << "emitting sig handle click";
                emit sigHandleClick(clicked_square);
            }
            if(jsonObject["type"] == "opponent disconnection") {
                emit sigOpponentDisconnection();
            }
        }
        catch (...) {
            qDebug() << "message received not json format";
        }
        qDebug() << "Received message from game port:" << message;
    }

    void gameDisconnected() const {
        qDebug() << "Disconnected from game port";
    }

    void onConnectGameSock() {
        qDebug() << "On connected game socket";
        connectGameSock();
    }

// widgets

	// try to login
	void onUpdateLogin(const std::string& username, const std::string& password) {
		login(username, password);
	}

	void onLogout() {
		logout();
	}

	// void onGetOnlinePlayers() {
	// 	std::pair<std::map<std::string, std::string>, int> resp = fetchOnlinePlayers();
	// 	if(resp.second != 200) {
	// 		qDebug() << "could not fetch session players";
	// 		return;
	// 	}
	// 	auto players = resp.first;
	// 	QString text;
	// 	qDebug() << "on get session players text1: " << text;
	// 	for (auto it = players.begin(); it != players.end(); it++) {
	// 		auto player = it->second.c_str();
	// 		qDebug() << "this->account.username: " << this->account.username;
	// 		qDebug() << "player: " << player;
	// 		if(player != this->account.username) {
	// 			text += player;
	// 			text += "\n";
	// 		}
	// 	}
	// 	qDebug() << "on get session players text2: " << text;
	// 	emit sigUpdateOnlinePlayers(text);
	// }

	void onCreateAccount(const std::string& username, const std::string& password, const std::string& dob) {
		qDebug() << "on create account";
		std::pair<std::string, int> resp = createAccount(username, password, dob);
		int code = resp.second;
		std::string body = resp.first;
		qDebug() << "status code: " << code;
		if(code == 200) {
			this->sigSignupState("");
		}
		else {
			if(body == "") {
				this->sigSignupState("failed to connect to server, try again");
			}
			else {
				std::string message = resp.first;
				QString state_message = QString(message.substr(12, message.size() - 14).c_str());
				qDebug() << "extracted error message: " << state_message;
				this->sigSignupState(state_message);
			}
		}
	}

    void closeOnlineGame() {
        qDebug() << "closing online game socket";
        if(socket_game) {
            socket_game->close();
            socket_game = nullptr;
        }
        qDebug() << "closed";
    }

public:
	Account account;
	GameInfo game_info_temp;
	GameInfo game_info;
	SessionManager() : uri(MY_URI), session(uri.getHost(), uri.getPort()) {
		session.setKeepAlive(true);
	};
	~SessionManager() {
		delete socket;
	}
	std::map<std::string, std::string> players;

	void logout() {
		if(socket_game) {
			socket_game->close();
			socket_game = nullptr;
		}
		socket->close();
		socket = nullptr;
	}
	
	void login(const std::string& _username, const std::string& _password) {
		this->account.username = _username;
		this->account.password = _password;
        connectSock(this->account.username.c_str(), this->account.password.c_str());
		qDebug() << "websocket connection attempt: ";
	}
	std::pair<std::string, int> createAccount(const std::string& username, const std::string& password, const std::string& dob) {
		makeRequests(HTTPRequest::HTTP_POST, "/signup", accountJson(username, password, dob));
		return {recvResponse(), getStatus()};
	}

	void sendMessage(QString message) {
		qDebug() << "sending message: " << message;
		socket->sendTextMessage(message);
	}

	void sendChallenge(const std::string& challenger, const std::string& challenged) {
		std::string msg = "{\"challenger\": \"" + challenger + "\", \"challenged\": \"" + challenged + "\"" + "}";
		sendMessage(msg.c_str());
	}

    void sendGameMessage(QString message) {
		qDebug() << "sending message: " << message;
		socket_game->sendTextMessage(message);
	}

	void sendClickedSquare(int x, int y) {
		qDebug() << "sending clicked square";
		QJsonObject jsonObject;
		jsonObject["type"] = "click";
        jsonObject["from"] = this->account.username.c_str();
		jsonObject["x"] = to_string(x).c_str();
		jsonObject["y"] = to_string(y).c_str();

		QJsonDocument doc(jsonObject);
		sendGameMessage(doc.toJson());
	}

private:

    void connectGameSock() {
        if(socket_game) {
            delete socket_game;
            socket_game = nullptr;
        }
        socket_game = new QWebSocket();
        auto gameId = this->game_info.challenger + "-" + this->game_info.challenged;
        connect(socket_game, &QWebSocket::connected, this, &SessionManager::gameConnected);
        connect(socket_game, &QWebSocket::textMessageReceived, this, &SessionManager::gameMessageReceived);
        connect(socket_game, &QWebSocket::disconnected, this, &SessionManager::gameDisconnected);
        QUrl qurl = QUrl(QString("ws://localhost:8000/ws/game/") + QString(gameId.c_str()) + QString("/") + QString(this->account.username.c_str()));

        socket_game->open(qurl);

        QEventLoop loop;
        connect(socket_game, &QWebSocket::connected, &loop, [&loop]() {
            qDebug() << "Connected game socket!";
            loop.quit();
        });
        connect(socket_game, &QWebSocket::errorOccurred, &loop, [&loop](QAbstractSocket::SocketError error) {
            qDebug() << "Game socket error:" << error;
            loop.quit();
        });
        loop.exec();
    }

    void connectSock(QString username, QString password) {
        if(socket) {
			delete socket;
			socket = nullptr;
		}
		socket = new QWebSocket();
		connect(socket, &QWebSocket::connected, this, &SessionManager::onConnected);
		connect(socket, &QWebSocket::textMessageReceived, this, &SessionManager::onMessageReceived);
		connect(socket, &QWebSocket::disconnected, this, &SessionManager::onDisconnected);

        QUrl qurl = QUrl("ws://localhost:8000/ws/login/" + username + "/" + password);
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

	/**
	 * @brief accountJson creates a json string for the account
	 */
	std::string accountJson(const std::string& username, const std::string& password, const std::string& dob) {
		std::string ret;
		static std::string msg = "a";
		msg += msg;
		ret = std::string("{") + "\"username\":\"" + username + "\",\"password\":\"" + password + "\",\"dob\":\"" + dob + "\",\"msg\":\"" + msg + "\"}";
		return ret;
	}

	/**
	 * @brief accountJson creates a json string for the account
	 */
	std::string accountJson(const std::string& username, const std::string& password) {
		std::string ret;
		ret = std::string("{") + "\"username\":\"" + username + "\",\"password\":\"" + password + "\"}";
		return ret;
	}
	std::string recvResponse() {
		std::stringstream ss;
		for (int i = 0; i < 6; i++) {
			try {
				istream& rs = session.receiveResponse(response);
				ss << rs.rdbuf();
				break;
			}
			catch (const Exception& e) {
				qDebug() << e.what();
				Poco::Thread::sleep(80);
			}
		}
		return ss.str();
	}
	int getStatus() const {
		return response.getStatus();
	}
	void makeRequests(std::string method, std::string path, std::string body="") {
		qDebug() << "Make request: " << path;
		request = HTTPRequest(method, path, HTTPMessage::HTTP_1_1);
		request.setContentType("application/json");
		request.setContentLength(body.length());
		std::ostream& os = session.sendRequest(request);
		os << body;
		os.flush();
		session.setTimeout(Poco::Timespan(10, 0));
	}
};

inline namespace Global {
   extern SessionManager session;
}

#endif
