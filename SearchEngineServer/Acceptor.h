/**
 * @brief 服务器监听类，用于封装acceptor socket的操作
 * @note 创建socket，绑定地址，监听，获取新连接
 */
#ifndef _ACCEPTOR_H
#define _ACCEPTOR_H

#include <iostream>

#include "InetAddress.h"
#include "Socket.h"
using std::cout;
using std::endl;

#define MAX_LISTEN_SIZE 128

class Acceptor {
 public:
  /**
   * @brief 构造函数
   * @param ip 服务器ip地址
   * @param port 服务器端口号
   */
  Acceptor(const string& ip, unsigned short port);
  /**
   * @brief 准备工作：设置地址复用，端口复用，绑定地址，监听
   */
  void ready();
  /**
   * @brief 获取新连接
   * @return int 新连接的文件描述符
   */
  int accept();
  /**
   * @brief 获取服务器文件描述符，用于epoll监听
   * @return int 文件描述符
   */
  int fd() const { return _sock.fd(); }

 private:
  Socket _sock;       // 服务器socket
  InetAddress _addr;  // 服务器地址

  // 设置地址复用
  void setReuseAddr();
  // 设置端口复用
  void setReusePort();
  // 绑定服务器地址和端口
  void bind();
  // 监听新连接
  void listen();
};

#endif  //_ACCEPTOR_H