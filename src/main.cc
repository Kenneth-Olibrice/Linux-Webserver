#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <string>
#include <cstring>
#include <cerrno>
#include <netdb.h>
#include <optional>

#include "SocketWrapper.hh"
#include "../include/HttpRequest.hh"


static const in_port_t http_port {htons (5000)};
constexpr int addr_family {AF_INET};
constexpr int addr_protocol {SOCK_DGRAM};

using namespace std;

int main () {
    std::string to_parse = "GET / HTTP/1.1\r\ncontent-length:12\r\ngoodbye:world\r\n\r\nhello,world!";
    std::optional o = HttpRequest::deserialize (to_parse);

    cout << "o has value: " << o.has_value () << endl;
    return 0;
}