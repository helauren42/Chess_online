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

#include <Poco/Net/HTTPClientSession.h>
#include <Poco/Net/HTTPMessage.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/URI.h>

#include <iostream>
#include <sstream>

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

// struct Date {
//     int day;
//     int month;
//     int year;
//     Date() {};
//     Date(int _day, int _month, int _year) : day(_day), month(_month), year(_year) {};
// };

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
    Account	() {};
    Account(const std::string& _username, const std::string& _password) : username(_username), password(_password) {};
    Account(const std::string& _username, const std::string& _password, const std::string& _dob) : username(_username), password(_password), dob(_dob) {};
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

    /**
     * @brief accountJson creates a json string for the account
     */
    std::string accountJson(const std::string& username, const std::string& password, const std::string& dob) {
        std::string ret;
        ret = std::string("{") + "\"username\":\"" + username + "\",\"password\":\"" + password + "\",\"dob\":\"" + dob + "\"}";
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
        for (int i = 0; i < 2; i++) {
            try {
                istream& rs = session.receiveResponse(response);
                ss << rs.rdbuf();
                break;
            }
            catch (const Exception& e){
                qDebug() << e.what();
                Poco::Thread::sleep(50);
            }
        }
        return ss.str();
    }
    int getStatus() const {
        return response.getStatus();
    }
    void makeRequests(std::string method, std::string path, std::string body) {
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
    Online() : uri(MY_URI), session(uri.getHost(), uri.getPort()) {
        session.setKeepAlive(true);
    };
    ~Online() {}

    std::pair<std::string, int> login(const std::string& username, const std::string& password) {
        makeRequests(HTTPRequest::HTTP_POST,"/login", accountJson(username, password));
        return {recvResponse(), getStatus()};
    }
    std::pair<std::string, int> createAccount(const std::string& username, const std::string& password, const std::string& dob) {
        makeRequests(HTTPRequest::HTTP_POST,"/signup", accountJson(username, password, dob));
        return {recvResponse(), getStatus()};
    }
    bool getLoggedIn() const { return loggedIn; };


};

inline namespace Global {
   extern Online online;
}

#endif
