#ifndef HTTP_CONNECTION_HH
#define HTTP_CONNECTION_HH

#include "../include/SocketWrapper.hh"
#include "../include/HttpMessage.hh"
#include <string_view>


class HttpConnection {
public:
  // One way to build connections is on top of an existing socket.
  HttpConnection (SocketWrapper &&sock) : sock_ (std::move (sock)) {}
  HttpConnection (HttpConnection &&other);

  // Another way is attempting to create a connection based on a url.
  static std::optional<HttpConnection> connect_to (std::string_view url);


  // Connections are non-copyable.
  HttpConnection (HttpConnection &other) = delete;
  HttpConnection& operator= (HttpConnection &other) = delete;
  
  void send_message (const HttpMessage &msg) const;
  HttpMessage receive_message () const;

private:
  SocketWrapper sock_;
};


#endif