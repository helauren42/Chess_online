#include <Poco/Net/HTTPClientSession.h>
#include <Poco/Net/HTTPMessage.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/URI.h>
#include <iostream>
#include <sstream>

#include "../FrontEnd/common.hpp"

using namespace Poco::Net;
using namespace Poco;
using namespace std;

#define MY_URI "http://127.0.0.1:8000"
#define PORT 8000

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
	};
};

struct Account {
	std::string username;
	std::string password;
	Date dob;
	Account	() {};
	Account(const std::string& _username, const std::string& _password) : username(_username), password(_password) {};
	Account(const std::string& _username, const std::string& _password, const Date& _dob) : username(_username), password(_password), dob(_dob) {};
};

class Online{
private:
	bool loggedIn = false;
	Account account;
	GameInfo gameInfo;
	URI uri;
	HTTPClientSession session;
	HTTPRequest request;
	HTTPResponse response;
	void makeRequests(std::string path, std::string body) {
		request = HTTPRequest(HTTPRequest::HTTP_GET, path, HTTPMessage::HTTP_1_1);
		std::ostream& os = session.sendRequest(request);
		os << body;
	}

public:
	Online() : uri(MY_URI) , session (uri.getHost(), uri.getPort()) {
		session.setKeepAlive(true);
	};
	~Online() {}
	std::string recvResponse() {
		istream& rs = session.receiveResponse(response);
		std::stringstream ss;
		ss << rs.rdbuf();
		return ss.str();
	}
	int getStatus() const {
		return response.getStatus();
	}

	void login(const std::string& username, const std::string& password) {}
	std::string accountJson(const std::string& username, const std::string& password, const Date& dob) {
		std::string ret;
		ret = std::string("{") + "\"username\":\"" + username + "\",\"password\":\"" + password + "\",\"dob\":\"" + to_string(dob.day) + "/" + to_string(dob.month) + "/" + to_string(dob.year) + "}";
		return ret;
	}
	std::pair<int, std::string> createAccount(const std::string& username, const std::string& password, const Date& dob) {
		makeRequests("/signup", accountJson(username, password, dob));
		return {getStatus(), recvResponse()};
	}
	// void logIn() { loggedIn = true; };
	// void logOut() { loggedIn = false; };
	bool getLoggedIn() const { return loggedIn; };
};

// int main() {
//     try {

//         URI uri("http://127.0.0.1:8000/");
//         HTTPClientSession session(uri.getHost(), uri.getPort());

//         cout << "get path: " << uri.getPath() << endl;

//         HTTPRequest request(HTTPRequest::HTTP_GET, uri.getPath(), HTTPMessage::HTTP_1_1);

//         session.sendRequest(request);

//         HTTPResponse response;
//         istream& rs = session.receiveResponse(response);

//         cout << "HTTP Status: " << response.getStatus() << rs.rdbuf() << endl;

//         stringstream ss;
//         ss << rs.rdbuf();
//         cout << "Response body:\n" << ss.str() << endl;
//     }
//     catch (const Exception& exc) {
//         cerr << "Error: " << exc.displayText() << endl;
//         return 1;
//     }

//     return 0;
// }
