#include "TcpConnection.h"

#include "EventLoop.h"

string TcpConnection::readMsg() {
  char buf[MAX_BUF_SIZE] = {};
  _sockIO.recvVarMsg(buf, MAX_BUF_SIZE);
  return buf;
}

void TcpConnection::sendMsg(const string& msg) {
  _sockIO.sendn(msg.c_str(), msg.size());
}

bool TcpConnection::isClosed() {
  char buf[1] = {};
  int ret = recv(_sockIO.fd(), buf, 1, MSG_PEEK);
  return (ret == 0);
}

void TcpConnection::handleNewConnection() {
  if (_onNewConnection) {
    _onNewConnection(shared_from_this());
  } else {
    throw std::runtime_error("no _onNewConnection callback");
  }
}
void TcpConnection::handleMessage() {
  if (_onMessage) {
    _onMessage(shared_from_this());
  } else {
    throw std::runtime_error("no _onMessage callback");
  }
}
void TcpConnection::handleClose() {
  if (_onClose) {
    _onClose(shared_from_this());
  } else {
    throw std::runtime_error("no _onClose callback");
  }
}

void TcpConnection::sendToLoop(FuncPtr&& cb) {
  _loop->readInLoop(std::move(cb));
}
