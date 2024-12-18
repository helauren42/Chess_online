#include "client.hpp"

int main() {
	Online online;
	std::pair<int, std::string> response = online.createAccount("test", "test", Date(1, 1, 2000));
	cout << response.first << ": " << response.second << endl;
	// online.makeRequests(HTTPRequest::HTTP_POST, "/signup", "");
	// online.makeRequests(HTTPRequest::HTTP_POST, "/signup", online.accountJson("test", "test", Date(1, 1, 2000)));
	// cout << online.getStatus() << ": " << online.recvResponse() << endl;
	return 0;
}
