// #ifndef #ifndef ONLINE_HPP
// #define ONLINE_HPP

// #include <iostream>

// #include "../../FrontEnd/common.hpp"
// #include <Poco/URI.h>
// #include <Poco/Net/HTTPClientSession.h>
// #include <Poco/Net/HTTPRequest.h>
// #include <Poco/Net/HTTPResponse.h>
// #include <Poco/Net/HTTPMessage.h>

// struct Date {
// 	int day;
// 	int month;
// 	int year;
// };

// struct GameInfo {
// 	GameMode mode;
// 	std::string opponent;
// 	void set(const GameMode &_mode, const std::string _opponent = "") {
// 		mode = _mode;
// 		opponent = _opponent;
// 	};
// };

// struct Account {
// 	std::string username;
// 	std::string password;
// 	Date dob;
// 	Account	() {};
// 	Account(const std::string& _username, const std::string& _password) : username(_username), password(_password) {};
// 	Account(const std::string& _username, const std::string& _password, const Date& _dob) : username(_username), password(_password), dob(_dob) {};
// };

// class O#ifndef ONLINE_HPP
// #define ONLINE_HPP

// #include <iostream>

// #include "../../FrontEnd/common.hpp"
// #include <Poco/URI.h>
// #include <Poco/Net/HTTPClientSession.h>
// #include <Poco/Net/HTTPRequest.h>
// #include <Poco/Net/HTTPResponse.h>
// #include <Poco/Net/HTTPMessage.h>

// struct Date {
// 	int day;
// 	int month;
// 	int year;
// };

// struct GameInfo {
// 	GameMode mode;
// 	std::string opponent;
// 	void set(const GameMode &_mode, const std::string _opponent = "") {
// 		mode = _mode;
// 		opponent = _opponent;
// 	};
// };

// struct Account {
// 	std::string username;
// 	std::string password;
// 	Date dob;
// 	Account	() {};
// 	Account(const std::string& _username, const std::string& _password) : username(_username), password(_password) {};
// 	Account(const std::string& _username, const std::string& _password, const Date& _dob) : username(_username), password(_password), dob(_dob) {};
// };

// class Online{
// private:
// 	bool loggedIn = false;
// 	Account account;
// 	GameInfo gameInfo;
// 	HTTPClientSession session;
// 	void makeRequests(std::string url) {}
// public:
// 	Online(const std::string uri) {
// 		session.open(Poco::URI(uri));
// 		session.setKeepAlive(true);
// 	};
// 	~Online() {}
// 	void login(const std::string& username, const std::string& password) {}
// 	void createAccount(const std::string& username, const std::string& password, const Date& dob) {

// 	}
// 	// void logIn() { loggedIn = true; };
// 	// void logOut() { loggedIn = false; };
// 	bool getLoggedIn() const { return loggedIn; };
// };

// bool operator==(const Account& lhs, const Account& rhs) {
// 	return lhs.username == rhs.username && lhs.password == rhs.password;
// }

// bool operator!=(const Account& lhs, const Account& rhs) {
// 	return lhs.username != rhs.username || lhs.password != rhs.password;
// }

// #endifnline{
// private:
// 	bool loggedIn = false;
// 	Account account;
// 	GameInfo gameInfo;
// 	HTTPClientSession session;
// 	void makeRequests(std::string url) {}
// public:
// 	Online(const std::string uri) {
// 		session.open(Poco::URI(uri));
// 		session.setKeepAlive(true);
// 	};
// 	~Online() {}
// 	void login(const std::string& username, const std::string& password) {}
// 	void createAccount(const std::string& username, const std::string& password, const Date& dob) {

// 	}
// 	// void logIn() { loggedIn = true; };
// 	// void logOut() { loggedIn = false; };
// 	bool getLoggedIn() const { return loggedIn; };
// };

// bool operator==(const Account& lhs, const Account& rhs) {
// 	return lhs.username == rhs.username && lhs.password == rhs.password;
// }

// bool operator!=(const Account& lhs, const Account& rhs) {
// 	return lhs.username != rhs.username || lhs.password != rhs.password;
// }

// #endifONLINE_HPP
// #define ONLINE_HPP

// #include <iostream>

// #include "../../FrontEnd/common.hpp"
// #include <Poco/URI.h>
// #include <Poco/Net/HTTPClientSession.h>
// #include <Poco/Net/HTTPRequest.h>
// #include <Poco/Net/HTTPResponse.h>
// #include <Poco/Net/HTTPMessage.h>

// struct Date {
// 	int day;
// 	int month;
// 	int year;
// };

// struct GameInfo {
// 	GameMode mode;
// 	std::string opponent;
// 	void set(const GameMode &_mode, const std::string _opponent = "") {
// 		mode = _mode;
// 		opponent = _opponent;
// 	};
// };

// struct Account {
// 	std::string username;
// 	std::string password;
// 	Date dob;
// 	Account	() {};
// 	Account(const std::string& _username, const std::string& _password) : username(_username), password(_password) {};
// 	Account(const std::string& _username, const std::string& _password, const Date& _dob) : username(_username), password(_password), dob(_dob) {};
// };

// class Online{
// private:
// 	bool loggedIn = false;
// 	Account account;
// 	GameInfo gameInfo;
// 	HTTPClientSession session;
// 	void makeRequests(std::string url) {}
// public:
// 	Online(const std::string uri) {
// 		session.open(Poco::URI(uri));
// 		session.setKeepAlive(true);
// 	};
// 	~Online() {}
// 	void login(const std::string& username, const std::string& password) {}
// 	void createAccount(const std::string& username, const std::string& password, const Date& dob) {
		
// 	}
// 	// void logIn() { loggedIn = true; };
// 	// void logOut() { loggedIn = false; };
// 	bool getLoggedIn() const { return loggedIn; };
// };

// bool operator==(const Account& lhs, const Account& rhs) {
// 	return lhs.username == rhs.username && lhs.password == rhs.password;
// }

// bool operator!=(const Account& lhs, const Account& rhs) {
// 	return lhs.username != rhs.username || lhs.password != rhs.password;
// }

// #endif
