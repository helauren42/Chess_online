#ifndef COMMON_HPP
#define COMMON_HPP

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
#include <iostream>
#include <sstream>
#include <memory>


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

using namespace Poco::Net;
using namespace Poco;
using namespace std;

#define MY_URI "http://127.0.0.1:8000"
#define PORT 8000

/**
 * @brief parses json formatted string into a map with key and value of strings, json string must be a valid dictionnary of strings of strings or behaviour is undefined
 * @param json the json formatted string as const reference
 */
inline std::map<std::string, std::string> jsonToMap(const std::string& json) noexcept {
	std::map<std::string, std::string> ret;
	size_t pos = 0;
	while (true)
	{
		std::string key;
		std::string value;
		if(pos >= json.size())
			break;

		size_t key_start = json.find_first_of("\"", pos);
		if(key_start == std::string::npos) {
			break;
		}

		size_t key_end = json.find_first_of("\"", key_start +1);
		if(key_end == std::string::npos) {
			break;
		}

		size_t value_start = json.find_first_of("\"", key_end +1);
		if(value_start == std::string::npos) {
			break;
		}
		
		size_t value_end = json.find_first_of("\"", value_start +1);
		if(value_end == std::string::npos) {
			break;
		}
		
		key = json.substr(key_start +1, key_end - key_start -1);
		value = json.substr(value_start +1, value_end - value_start -1);
		ret[key] = value;
		pos = json.find_first_of(",", value_end);
	}
	return ret;
}

struct GameInfo {
	GameMode mode;
	std::string opponent;
	void set(const GameMode &_mode, const std::string _opponent = "") {
		mode = _mode;
		opponent = _opponent;
	};
};

struct Account {
	std::string username;
	std::string password;
	std::string dob;
	int id;
	Account	() {};
	Account(const std::string& _username, const std::string& _password) : username(_username), password(_password) {};
	Account(const std::string& _username, const std::string& _password, const std::string& _dob) : username(_username), password(_password), dob(_dob) {};
};

class WebSocketClient : public QObject {
	Q_OBJECT
private:
	QWebSocket *socket;
public:
	WebSocketClient(QString username, QObject *parent = nullptr) : QObject(parent) {
		socket = new QWebSocket("My WebSocket Client", QWebSocketProtocol::VersionLatest, this);
		connect(socket, &QWebSocket::connected, this, &WebSocketClient::onConnected);
		connect(socket, &QWebSocket::textMessageReceived, this, &WebSocketClient::onTextMessageReceived);
		connect(socket, &QWebSocket::disconnected, this, &WebSocketClient::onDisconnected);
        QUrl qurl = QUrl("ws://localhost:8000/ws/" + username);
        qDebug() <<  "qurl: " << qurl;
		socket->open(qurl);

        QEventLoop loop;
        connect(socket, &QWebSocket::connected, &loop, &QEventLoop::quit);
        connect(socket, QOverload<QAbstractSocket::SocketError>::of(&QWebSocket::error),
                &loop, &QEventLoop::quit);
        loop.exec();  // Blocks until the connection is established or an error occurs
	}

public slots:
	void onConnected() {
		qDebug() << "Connected to server";
	}

	void onTextMessageReceived(QString message) {
		qDebug() << "Received message from server:" << message;
	}

	void onDisconnected() {
		qDebug() << "Disconnected from server";
	}

	void sendMessage(QString message) {
		socket->sendTextMessage(message);
	}

};

class Online{
private:
	bool loggedIn = false;
	GameInfo gameInfo;
	URI uri;
	HTTPClientSession session;
	HTTPRequest request;
	HTTPResponse response;

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
			catch (const Exception& e){
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
		qDebug() << "Make request";
		request = HTTPRequest(method, path, HTTPMessage::HTTP_1_1);
		request.setContentType("application/json");
		request.setContentLength(body.length());
		std::ostream& os = session.sendRequest(request);
		os << body;
		os.flush();
		session.setTimeout(Poco::Timespan(10, 0));
		qDebug() << "set timeout";
	}

public:
	Account account;
	std::unique_ptr<WebSocketClient> ws;
	Online() : uri(MY_URI), session(uri.getHost(), uri.getPort()) {
		session.setKeepAlive(true);
	};
	~Online() {}
	std::map<std::string, std::string> players;

	std::pair<std::string, int> logout() {
		qDebug() << "sending log out request";
		makeRequests(HTTPRequest::HTTP_POST, "/logout", accountJson(this->account.username, this->account.password));
		ws.reset();
		ws = nullptr;
		return {recvResponse(), getStatus()};
	}
	std::pair<std::string, int> login(const std::string& _username, const std::string& _password) {
		makeRequests(HTTPRequest::HTTP_POST, "/login", accountJson(_username, _password));
		this->account.username = _username;
		this->account.password = _password;
		std::string message = recvResponse();
		qDebug() << "response message: " << message;
		int status = getStatus();
		if(status == 200)
            ws = std::make_unique<WebSocketClient>(this->account.username.c_str(), nullptr);
		qDebug() << "websocket made: ";
		return {message, status};
	}
	std::pair<std::string, int> createAccount(const std::string& username, const std::string& password, const std::string& dob) {
		makeRequests(HTTPRequest::HTTP_POST, "/signup", accountJson(username, password, dob));
		return {recvResponse(), getStatus()};
	}
	// getMenu basically
	std::pair<std::map<std::string, std::string>, int> fetchOnlinePlayers() {
		makeRequests(HTTPRequest::HTTP_GET, "/menu");
		auto json = recvResponse();
		players = jsonToMap(json);
		qDebug() << "players: ";
		for(auto it = players.begin(); it != players.end(); it++) {
			qDebug() << it->second;
		}
		return {players, getStatus()};
	}

	void sendChallenge(const std::string& challenger, const std::string& challenged) {
		std::string msg = "{\"challenger\": \"" + challenger + "\", \"challenged\": \"" + challenged + "\"" + "}";
		ws->sendMessage(msg.c_str());
	}

	bool getLoggedIn() const { return loggedIn; };
};

inline namespace Global {
   extern Online online;
}

#endif
