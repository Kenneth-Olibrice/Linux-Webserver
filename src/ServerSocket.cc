#include "ServerSocekt.hh"

#include <cstring>
#include <cerrno>
#include <iostream>

static const in_port_t http_port {htons (80)};

ServerSocket::ServerSocket () {
    int sock = socket (AF_INET, SOCK_STREAM, 0); // 0 = neither cloexec or nonblock flags are set.
    
    sockaddr_in addr {};
    addr.sin_family = AF_INET;
    addr.sin_port = http_port;
    addr.sin_addr.s_addr = INADDR_ANY;
   
    int result = bind (sock, (sockaddr*)&addr, sizeof (addr)); // TODO: Find a safer way to do this than C-style casting.

    if (result == -1) {
        std::cout << "Bind failed with error " << std::strerror(errno)<< std::endl;
        throw std::runtime_error ("IT'S THE END OF THE WORLD");
    }
}