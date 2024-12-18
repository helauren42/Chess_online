#include <Poco/Net/HTTPClientSession.h>
#include <Poco/Net/HTTPRequest.h>
#include <Poco/Net/HTTPResponse.h>
#include <Poco/URI.h>
#include <iostream>
#include <sstream>

using namespace Poco::Net;
using namespace Poco;
using namespace std;

int main() {
    try {
        URI uri("http://127.0.0.1:8000/");

        HTTPClientSession session(uri.getHost(), uri.getPort());

        cout << "get path: " << uri.getPath() << endl;

        HTTPRequest request(HTTPRequest::HTTP_GET, uri.getPath(), HTTPMessage::HTTP_1_1);

        session.sendRequest(request);

        HTTPResponse response;
        istream& rs = session.receiveResponse(response);

        cout << "HTTP Status: " << response.getStatus() << rs.rdbuf() << endl;

        stringstream ss;
        ss << rs.rdbuf();
        cout << "Response body:\n" << ss.str() << endl;
    }
    catch (const Exception& exc) {
        cerr << "Error: " << exc.displayText() << endl;
        return 1;
    }

    return 0;
}
