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

int main () {
    sockaddr_in addr {};
    addr.sin_family = AF_INET;
    addr.sin_port = http_port;
    addr.sin_addr.s_addr = INADDR_ANY;
  

    std::optional sock {SocketWrapper::make_socket (AF_INET, SOCK_STREAM, 0)};
    if (!sock.has_value ()) {
        std::cout << "Could not make socket\n";
        std::cout << strerror (errno) << "\n";
        return -1;
    }

    SocketWrapper &s {sock.value ()};
    
    int res1 = s.bind ((sockaddr*)&addr, sizeof (addr));
    if (res1 == -1) {
        std::cout << "Error binding.\n";
        std::cout << strerror (errno) << "\n";
        return -1;
    }

    int res2 = s.listen (1);
    if (res2 == -1) {
        std::cout << "Listen failed.\n" << std::endl;
    }

    auto candidate = s.accept ();
    if (!candidate.has_value ()) {
        std::cout << "Accept failed.\n";
        std::cout << strerror (errno) << std::endl;
        return -1;
    }

    SocketWrapper &sender = candidate.value ();
    std::string msg = "Hello, world!";

    sender.send (msg, 0);

    return 0;
}