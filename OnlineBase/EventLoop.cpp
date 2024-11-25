#include "EventLoop.h"

void EventLoop::loop() {
  _isLooping = true;
  _timer.start();
  while (_isLooping) {
    int nready = _epoll.epollWait();
    for (int i = 0; i < nready; ++i) {
      struct epoll_event ev = _epoll.getReadyEvent(i);
      if (ev.data.fd == _acceptor.fd()) {
        if (ev.events & EPOLLIN) {
          handleNewConnection();
        }
      } else if (ev.data.fd == _eventfd.fd()) {
        if (ev.events & EPOLLIN) {
          _eventfd.handleRead();
          dealResult();
        }
      } else if (ev.data.fd == STDIN_FILENO) {
        string line;
        if (std::getline(std::cin, line), std::cin.eof()) {
          fprintf(stdout, "Reached EOF (Ctrl + D). Exiting the event loop.\n");
          unloop();
        }
      } else if (ev.events & EPOLLIN) {
        handleMessage(ev.data.fd);
      }
    }
  }
  fprintf(stdout, "event loop stoped\n");
}

void EventLoop::handleNewConnection() {
  int peerfd = _acceptor.accept();
  _conns[peerfd] = std::make_shared<TcpConnection>(peerfd, this);
  _epoll.addEvent(peerfd);

  _conns[peerfd]->setNewConnectionCallback(_onNewConnection);
  _conns[peerfd]->setMessageCallback(_onMessage);
  _conns[peerfd]->setCloseCallback(_onClose);

  _conns[peerfd]->handleNewConnection();
}

void EventLoop::handleMessage(int peerfd) {
  auto it = _conns.find(peerfd);
  if (it != _conns.end()) {
    bool flag = it->second->isClosed();  // 先判断对端是否关闭
    if (flag) {
      it->second->handleClose();
      handleClose(peerfd);
      return;
    }
    it->second->handleMessage();
  } else {
    perror("no such connection");
  }
}
void EventLoop::handleClose(int peerfd) {
  _epoll.delEvent(peerfd);
  _conns.erase(peerfd);
}

void EventLoop::readInLoop(FuncPtr&& cb) {
  {
    lock_guard<mutex> lg(_mutex);
    _pending.emplace_back(std::move(cb));
  }
  _eventfd.wakeup();
}

void EventLoop::dealResult() {
  vector<FuncPtr> tmp;
  {
    lock_guard<mutex> lg(_mutex);
    _pending.swap(tmp);
  }
  for (auto& cb : tmp) {
    cb();
  }
}