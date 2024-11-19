#include "Epoll.h"

void Epoll::addEvent(int fd, EPOLL_EVENTS events) {
  struct epoll_event ev;
  ev.events = events;
  ev.data.fd = fd;
  if (epoll_ctl(_epfd, EPOLL_CTL_ADD, fd, &ev) == -1) {
    throw std::runtime_error("epoll_ctl add error");
  }
}

void Epoll::delEvent(int fd) {
  if (epoll_ctl(_epfd, EPOLL_CTL_DEL, fd, nullptr) == -1) {
    throw std::runtime_error("epoll_ctl del error");
  }
}

int Epoll::epollWait(int timeout) {
  int nready = epoll_wait(_epfd, _events.data(), _events.size(), timeout);
  if (nready == -1) {
    if (errno == EINTR) {
      perror("epoll_wait EINTR");
      return 0;
    }
    throw std::runtime_error("epoll_wait error");
  } else if (_events.size() <= (size_t)nready) {
    _events.resize(_events.size() * 2);
  }
  return nready;
}