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


signals:

	void    sigPlayerConnection();
    void    sigGetOnlinePlayers();
	void    sigUpdateOnlinePlayers(const QString& text);
	void    sigSignupState(QString msg);
	void	sigMakeLogin();
	void	sigFaultyLogin(const QString& msg);
	void	sigInvite();
	void	sigLaunchOnlineGame();

public slots:

// Websockets
	void onNewPlayerConnection() {
		emit sigPlayerConnection();
	};

	void onConnected() {
		qDebug() << "Connected to server";
	}

	void onMessageReceived(QString message) {
		if(message == "update connections") {
			this->sigGetOnlinePlayers();
			return;
		}

		try {
            nlohmann::json jsonObject = nlohmann::json::parse(message.toStdString());
			if(jsonObject["type"] == "challenge") {
				std::string opponent = jsonObject["from"];
				bool color = jsonObject["color"] == "white" ? PLAYER_COLOR::WHITE : PLAYER_COLOR::BLACK;
				game_info.set(GAMEMODE::ONLINE, opponent, color);
				emit sigInvite();
			}
            if(jsonObject["type"] == "start online game") {
				std::string opponent = jsonObject["opponent"];
				bool color = jsonObject["color"] == "white" ? PLAYER_COLOR::WHITE : PLAYER_COLOR::BLACK;
				game_info.set(GAMEMODE::ONLINE, opponent, color);
				// emit sigInvite();
                emit sigLaunchOnlineGame();
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
        // QMessageBox::information("Invite sent, waiting for response");
	}

// widgets

	// try to login
	void onUpdateLogin(const std::string& username, const std::string& password) {
		std::pair<std::string, int> resp = login(username, password);
		if(resp.second == 200)
			emit this->sigMakeLogin();
		else
			emit this->sigFaultyLogin(resp.first.c_str());
	}

	void onLogout() {
		logout();
	}

	void onGetOnlinePlayers() {
		std::pair<std::map<std::string, std::string>, int> resp = fetchOnlinePlayers();
		if(resp.second != 200) {
			qDebug() << "could not fetch session players";
			return;
		}
		auto players = resp.first;
		QString text;
		qDebug() << "on get session players text1: " << text;
		for (auto it = players.begin(); it != players.end(); it++) {
			auto player = it->second.c_str();
			qDebug() << "this->account.username: " << this->account.username;
			qDebug() << "player: " << player;
			if(player != this->account.username) {
				text += player;
				text += "\n";
			}
		}
		qDebug() << "on get session players text2: " << text;
		emit sigUpdateOnlinePlayers(text);
	}

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

public:

    void connectSock(QString username) {
        if(!socket) {
            delete socket;
            socket = nullptr;
        }
        socket = new QWebSocket();
        connect(socket, &QWebSocket::connected, this, &SessionManager::onConnected);
        connect(socket, &QWebSocket::textMessageReceived, this, &SessionManager::onMessageReceived);
        connect(socket, &QWebSocket::disconnected, this, &SessionManager::onDisconnected);
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

public:
	// MainWindow *window;
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

	void sendMessage(QString message) {
        qDebug() << "sending message: " << message;
		socket->sendTextMessage(message);
	}

	std::pair<std::string, int> logout() {
		qDebug() << "sending log out request";
		makeRequests(HTTPRequest::HTTP_POST, "/logout", accountJson(this->account.username, this->account.password));
		return {recvResponse(), getStatus()};
	}
	
	std::pair<std::string, int> login(const std::string& _username, const std::string& _password) {
		try {
			makeRequests(HTTPRequest::HTTP_POST, "/login", accountJson(_username, _password));
		}
		catch (const std::exception& e) {
			return {"Could not connect to servers", 0};
		}
		this->account.username = _username;
		this->account.password = _password;
		std::string message = recvResponse();
		qDebug() << "response message: " << message;
		int status = getStatus();
		if(status == 200) {
			connectSock(this->account.username.c_str());
		}
		qDebug() << "websocket made: ";
		return {message, status};
	}
	std::pair<std::string, int> createAccount(const std::string& username, const std::string& password, const std::string& dob) {
		makeRequests(HTTPRequest::HTTP_POST, "/signup", accountJson(username, password, dob));
		return {recvResponse(), getStatus()};
	}

	std::pair<std::map<std::string, std::string>, int> fetchOnlinePlayers() {
		makeRequests(HTTPRequest::HTTP_GET, "/online_players");
		auto json = recvResponse();
		qDebug() << "JSON ONLINE PLAYERS FETCH:" << json.c_str();
		players = jsonToMap(json);
		qDebug() << "playersss: ";
		for(auto it = players.begin(); it != players.end(); it++) {
			qDebug() << it->second;
		}
		return {players, getStatus()};
	}

	void sendChallenge(const std::string& challenger, const std::string& challenged) {
		std::string msg = "{\"challenger\": \"" + challenger + "\", \"challenged\": \"" + challenged + "\"" + "}";
		sendMessage(msg.c_str());
	}

};

inline namespace Global {
   extern SessionManager session;
}

#endif
