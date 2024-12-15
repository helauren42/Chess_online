// #include "../INC/MyCppLib/API/Api.hpp"

// int main() {
// 	int socketfd = socket(AF_INET, SOCK_STREAM, 0);
// 	struct sockaddr_in addr;
// 	addr.sin_family = AF_INET;
// 	addr.sin_port = htons(8000);
// 	addr.sin_addr.s_addr = inet_addr("127.0.0.1");
// 	connect(socketfd, (struct sockaddr *)&addr, sizeof(addr));

// 	std::string http_request = "GET / HTTP/1.1\r\n"
// 		"Host: 127.0.0.1:8000\r\n"
// 		"Connection: close\r\n\r\n";
// 	send(socketfd, http_request.c_str(), http_request.length(), 0);

// 	char buffer[4096];
// 	int bytes_read = 0;
// 	while ((bytes_read = read(socketfd, buffer, sizeof(buffer) - 1)) > 0) {
// 		buffer[bytes_read] = '\0';
// 		HttpResponse httpResp(buffer);
// 		std::cout << httpResp << std::endl;
// 	}

// 	return 0;
// }
