#ifndef SOCKET_WRAPPER_H
#define SOCKET_WRAPPER_H

#include <optional>
#include <unistd.h>
#include <string_view>
#include <sys/socket.h>
#include <vector>


class SocketWrapper {
public:
  static std::optional<SocketWrapper> make_socket (int domain, int type, int protocol);
  SocketWrapper (SocketWrapper &other) = delete;
  SocketWrapper &operator= (SocketWrapper &other) = delete;

  // Move operators. We may want these in the future, but for now they are deleted.
  SocketWrapper (SocketWrapper &&other);
  // SocketWrapper &operator= (SocketWrapper &&other) = delete; // TODO: We may want this

  ~SocketWrapper () {close (fd_);};

  int bind (const struct sockaddr *addr, socklen_t addr_size);
  int listen (int backlog);
  std::optional<SocketWrapper> accept ();

  ssize_t send (std::string_view bytes, int flags);
  ssize_t recv (std::string buf, size_t bytes, int flags);

protected:
  explicit SocketWrapper (int sock_fd) : fd_ (sock_fd) {};
  int fd_ {};
};

#endif