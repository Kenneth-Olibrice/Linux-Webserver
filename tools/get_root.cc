#include <string>
#include <iostream>
#include <optional>
#include <cerrno>
#include <cstring>

#include "../include/HttpConnection.hh"
#include "../include/HttpRequest.hh"

using namespace std;


int main (int argc, const char* argv[]) {
    if (argc != 2) {
        cout << "Incorrectly formatted usage. Proper usage is get_root <url>" << endl;
        return -1;
    }

    string url {argv[1]};
    optional connection = HttpConnection::connect_to (url);

    if (!connection.has_value ()) {
        cout << "Could not connect. Reason: " << strerror (errno) << endl;
        return -1;
    }

    HttpRequest request {};
    request.set_method (HttpMethod::GET);
    request.set_uri ("/");
    request.set_version (1,1);
    request.set_header ("host", url);

    connection.value ().send_message (request);

    
    return 0;
}