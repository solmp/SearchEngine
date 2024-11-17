#include "EventFd.h"

EventFd::EventFd() : _evfd(eventfd(0, 0)) {
  if (_evfd == -1) {
    throw std::runtime_error("eventfd create error");
  }
};

void EventFd::handleRead() {
  int64_t flag;
  int ret = read(_evfd, &flag, sizeof(flag));
  if (ret == -1) {
    if (errno == EINTR) {
      perror("eventfd handleRead EINTR");
      return;
    }
    throw std::runtime_error("eventfd handleRead error");
  } else if (ret == 0) {
    throw std::runtime_error("eventfd peer close");
  }
}

void EventFd::wakeup() {
  int64_t flag = 1;
  int ret = write(_evfd, &flag, sizeof(flag));
  if (ret == -1) {
    if (errno == EINTR) {
      perror("eventfd wakeup EINTR");
      return;
    }
    throw std::runtime_error("eventfd wakeup error");
  }
}