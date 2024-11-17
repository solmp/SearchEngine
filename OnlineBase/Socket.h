/**
 * @brief socket封装类
 */
#ifndef _SOCKET_H
#define _SOCKET_H

#include <sys/socket.h>
#include <unistd.h>

#include "NonCopyable.h"

class Socket : NonCopyable {
 public:
  Socket() : _fd(socket(AF_INET, SOCK_STREAM, 0)) {
    if (_fd == -1) {
      throw std::runtime_error("socket error");
    }
  }
  /**
   * @brief 通过文件描述符构造socket
   */
  explicit Socket(int fd) : _fd(fd) {}
  ~Socket() { close(_fd); }
  int fd() const { return _fd; }

 private:
  int _fd;
};

#endif  //_SOCKET_H