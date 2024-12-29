#ifndef COMMON_H
#define COMMON_H

#include "../BackEnd/inc/Utils.hpp"

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

enum class GAMEMODE {
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
	GAMEMODE mode;
	std::string opponent;
	bool color;
	void reset() {
		mode = GAMEMODE::OFF;
		opponent = "";
		color = false;
	}
	void set(const GAMEMODE &_mode, const std::string& _opponent = "", const bool& _color = false) {
		mode = _mode;
		opponent = _opponent;
		color = _color;
	};
	GameInfo& operator=(const GameInfo& rhs) {
        this->set(rhs.mode, rhs.opponent, rhs.color);
		return *this;
	}
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

#endif
