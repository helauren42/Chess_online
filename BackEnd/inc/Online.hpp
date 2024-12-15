#ifndef ONLINE_HPP
#define ONLINE_HPP

#include <iostream>

#include "../../FrontEnd/common.hpp"

struct Date {
	int day;
	int month;
	int year;
};

struct GameInfo {
	GameMode mode;
	std::string opponent;
	void set(const GameMode &_mode, const std::string _opponent = "") {
		mode = _mode;
		opponent = _opponent;
	};0
};

struct Account {
	std::string username;
	std::string password;
	Date dob;
	Account(const std::string& _username, const std::string& _password) : username(_username), password(_password) {};
	Account(const std::string& _username, const std::string& _password, const Date& _dob) : username(_username), password(_password), dob(_dob) {}
	void set(const std::string& _username, const std::string& _password) {
		username = _username;
		password = _password;
	}
	void set(const std::string& _username, const std::string& _password, const Date& _dob) {
		username = _username;
		password = _password;
		dob = _dob;
	}
};

bool operator==(const Account& lhs, const Account& rhs) {
	return lhs.username == rhs.username && lhs.password == rhs.password;
}

bool operator!=(const Account& lhs, const Account& rhs) {
	return lhs.username != rhs.username || lhs.password != rhs.password;
}

#endif