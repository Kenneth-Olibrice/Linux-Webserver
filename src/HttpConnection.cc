#include "HttpConnection.hh"
#include <netdb.h>

using namespace std;

// HTTP uses port 80.
constexpr string port {"80"};

void HttpConnection::send_message (const HttpMessage &msg) const {
    sock_.send (msg.serialize (), 0);
}

HttpConnection::HttpConnection (HttpConnection &&other) : sock_ (move (other.sock_)) {

}

optional<HttpConnection> HttpConnection::connect_to (string_view url) {
    // Implementation courtesy of [https://stackoverflow.com/questions/30470505/http-request-using-sockets-in-c].
    struct addrinfo *results {};
    struct addrinfo hints {.ai_family = AF_UNSPEC, .ai_socktype = SOCK_STREAM};

    int addrinfo_result = getaddrinfo (url.data (), port.c_str (), &hints, &results);
    if (addrinfo_result == -1)
      return nullopt;

    
    optional sock_opt = SocketWrapper::make_socket (results->ai_family, results->ai_socktype, results->ai_protocol);
    if (!sock_opt.has_value ())
        return nullopt;

    SocketWrapper &sock = sock_opt.value ();

    

    int connect_result = sock.connect (results->ai_addr, results->ai_addrlen);
    if (connect_result == -1)
    {
      freeaddrinfo (results);
      return nullopt;
    }
        
    freeaddrinfo (results);
    return HttpConnection (move (sock));
}