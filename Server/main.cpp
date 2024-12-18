#include "client.hpp"

int main() {
	Online online;
		online.makeRequests("/");
		cout << online.recvResponse();

	return 0;
}
