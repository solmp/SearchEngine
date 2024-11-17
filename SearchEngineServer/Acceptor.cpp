#include "Acceptor.h"

Acceptor::Acceptor(const string& ip, unsigned short port) : _addr(ip, port) {}

void Acceptor::ready() {
  setReuseAddr();
  setReusePort();
  bind();
  listen();
}

int Acceptor::accept() {
  int peerfd = ::accept(_sock.fd(), nullptr, nullptr);
  if (peerfd == -1) {
    throw std::runtime_error("accept error");
  }
  cout << "client connected: " << peerfd << endl;
  return peerfd;
}

void Acceptor::setReuseAddr() {
  int on = 1;
  if (setsockopt(_sock.fd(), SOL_SOCKET, SO_REUSEADDR, &on, sizeof(on)) == -1) {
    throw std::runtime_error("setsockopt reuseaddr error");
  }
}

void Acceptor::setReusePort() {
  int on = 1;
  if (setsockopt(_sock.fd(), SOL_SOCKET, SO_REUSEPORT, &on, sizeof(on)) == -1) {
    throw std::runtime_error("setsockopt reuseport error");
  }
}

void Acceptor::bind() {
  if (::bind(_sock.fd(), (struct sockaddr*)_addr.getInetAddressPtr(),
             sizeof(struct sockaddr)) == -1) {
    throw std::runtime_error("bind error");
  }
}

void Acceptor::listen() {
  if (::listen(_sock.fd(), MAX_LISTEN_SIZE) == -1) {
    throw std::runtime_error("listen error");
  }
}