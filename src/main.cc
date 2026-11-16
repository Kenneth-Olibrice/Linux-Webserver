#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <string>
#include <cstring>
#include <cerrno>
#include <netdb.h>

#include "SocketWrapper.hh"


static const in_port_t http_port {htons (5000)};
constexpr int addr_family {AF_INET};
constexpr int addr_protocol {SOCK_DGRAM};

int main () {
    
}