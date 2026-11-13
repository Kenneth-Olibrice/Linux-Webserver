#include "SocketWrapper.hh"
#include <netdb.h>

using namespace std;


optional<SocketWrapper> SocketWrapper::make_socket (int domain, int type, int protocol) {
    int sock = socket (domain, type, protocol); // 0 = neither cloexec or nonblock flags are set.
    
    if (sock == -1) {
        return nullopt; 
    } else {
        return SocketWrapper (sock);
    }
}

int SocketWrapper::bind (const struct sockaddr *addr, socklen_t addr_size) {
    return ::bind (fd_, addr, addr_size);
}

int SocketWrapper::listen (int backlog) {
    return ::listen (fd_, backlog);
}

optional<SocketWrapper> SocketWrapper::accept () {
    int result {::accept (fd_, NULL, NULL)};
    if (result == -1) {
        return nullopt;
    } else {
        return SocketWrapper (result);
    }
}

SocketWrapper::SocketWrapper (SocketWrapper &&other) {
    fd_ = other.fd_;
    other.fd_ = -1; // Invalidate other file descriptor so it cannot be used anymore.
}

ssize_t SocketWrapper::send (string_view bytes, int flags) {
    return ::send (fd_, bytes.data (), bytes.size (), flags);
}