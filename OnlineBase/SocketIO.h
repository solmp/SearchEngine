/**
 * @brief socket网络通信类
 */
#ifndef _SOCKETIO_H
#define _SOCKETIO_H

#include <unistd.h>

#include <iostream>

#include "NonCopyable.h"

class SocketIO : NonCopyable {
 public:
  /**
   * @brief 通过文件描述符构造socket网络通信连接
   */
  explicit SocketIO(int fd) : _fd(fd) {}
  ~SocketIO() { close(_fd); }

  /**
   * @brief 接收n个字节
   * @param buf 数据缓冲区
   * @param len 接收字节数
   */
  size_t recvn(char* buf, size_t len);
  /**
   * @brief 接收一行数据
   * @param buf 数据缓冲区
   * @param len 最大接收字节数
   */
  size_t recvLine(char* buf, size_t len);
  /**
   * @brief 接收变长消息
   * @param buf 数据缓冲区
   * @param max_len 最大接收字节数
   * @param flag 接收标志
   */
  size_t recvVarMsg(char* buf, size_t max_len, int flag = 0);
  /**
   * @brief 发送n个字节
   * @param buf 数据缓冲区
   * @param len 发送字节数
   */
  size_t sendn(const char* buf, size_t len);
  /**
   * @brief 发送变长消息
   * @param buf 数据缓冲区
   * @param len 发送字节数
   */
  size_t sendVarMsg(const char* buf, size_t len);
  int fd() const { return _fd; }

 private:
  int _fd;
};

#endif  //_SOCKETIO_H