#include "SocketIO.h"

#include <sys/socket.h>

size_t SocketIO::recvn(char* buf, size_t len) {
  size_t left = len;
  char* p = buf;
  while (left > 0) {
    int ret = recv(_fd, p, left, 0);
    if (ret == -1) {
      if (errno == EINTR) {
        perror("recvn EINTR");
        continue;
      }
      throw std::runtime_error("recvn error");
    } else if (ret == 0) {
      perror("peer close connection");
      break;
    } else {
      left -= ret;
      p += ret;
    }
  }
  return len - left;
}

size_t SocketIO::recvLine(char* buf, size_t len) {
  size_t left = len - 1;
  char* p = buf;
  while (left > 0) {
    int ret = recv(_fd, p, left, MSG_PEEK);
    if (ret == -1) {
      if (errno == EINTR) {
        perror("recvLine EINTR");
        continue;
      }
      throw std::runtime_error("recvLine error");
    } else if (ret == 0) {
      perror("peer close connection");
      break;
    }
    for (int idx = 0; idx < ret; ++idx) {
      if (p[idx] == '\n') {
        size_t nread = idx + 1;
        recvn(p, nread);
        p[nread] = '\0';
        return len - left + idx;
      }
    }
    recvn(p, ret);
    left -= ret;
    p += ret;
  }
  p[0] = '\0';
  return len - left - 1;
}

size_t SocketIO::recvVarMsg(char* buf, size_t max_len, int flag) {
  return recv(_fd, buf, max_len, flag);
}

size_t SocketIO::sendn(const char* buf, size_t len) {
  size_t left = len;
  const char* p = buf;
  while (left > 0) {
    int ret = send(_fd, p, left, 0);
    if (ret == -1) {
      if (errno == EINTR) {
        perror("sendn EINTR");
        continue;
      }
      throw std::runtime_error("sendn error");
    }
    left -= ret;
    p += ret;
  }
  return len - left;
}

size_t SocketIO::sendVarMsg(const char* buf, size_t len) {
  return send(_fd, buf, len, 0);
}