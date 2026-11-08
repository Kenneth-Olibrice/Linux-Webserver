#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <iostream>
#include <string>
#include <cstring>
#include <cerrno>

const in_port_t http_port {htons (80)};

int main () {
    int sock = socket (AF_INET, SOCK_STREAM, 0); // 0 = neither cloexec or nonblock flags are set.
    
    sockaddr_in addr {};
    addr.sin_family = AF_INET;
    addr.sin_port = http_port;
    addr.sin_addr.s_addr = INADDR_ANY;

    int result = bind (sock, (sockaddr*)&addr, sizeof (addr)); // TODO: Find a safer way to do this than C-style casting.

    if (result == -1) {
        std::cout << "Bind failed with error " << std::strerror(errno)<< std::endl;
        return -1;
    }
    result = listen (sock, 1);
    if (result == -1) {
        std::cout << "Listen failed." << std::endl;
        return -1;
    }
    
    sockaddr client_addr {};
    socklen_t l = (socklen_t)sizeof (client_addr);

    int fd =  accept (sock, &client_addr, &l);

    // std::cout << "Connected. " << result << std::endl;

    std::string buf {};
    buf.reserve (100);
    
    while (true) {
        ssize_t num_received = recv (fd, static_cast<void*> (&buf[0]), buf.capacity (), 0);
        if (num_received == -1) {
            std::cout << std::strerror (errno) << std::endl;
            break;
        }

        if (num_received == 0)
            continue;
        
        std::cout << buf << std::endl;
    }

    return 0;
}