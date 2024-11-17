/**
 * @brief Tcp服务器类
 * @note 封装了Acceptor和EventLoop
 */
#ifndef _TCPSERVER_H
#define _TCPSERVER_H

#include "EventLoop.h"

class TcpServer {
 public:
  /**
   * @brief 构造函数
   * @param ip 服务器ip地址
   * @param port 服务器端口号
   */
  TcpServer(const string& ip, unsigned short port)
      : _acceptor(ip, port), _loop(_acceptor) {}
  /**
   * @brief 启动服务器
   * @note 开始监听，进入事件循环
   */
  void start() {
    _acceptor.ready();
    _loop.loop();
  }
  /**
   * @brief 停止服务器
   */
  void stop() { _loop.unloop(); }
  /**
   * @brief 设置回调函数
   * @note 三个事件: 连接建立、消息到达、连接断开
   * @param cb1 新连接回调函数
   * @param cb2 消息回调函数
   * @param cb3 关闭回调函数
   */
  void setAllCallback(TcpConnectCallback&& cb1, TcpConnectCallback&& cb2,
                      TcpConnectCallback&& cb3) {
    _loop.setNewConnectionCallback(std::move(cb1));
    _loop.setMessageCallback(std::move(cb2));
    _loop.setCloseCallback(std::move(cb3));
  }

 private:
  Acceptor _acceptor;  // 服务器监听
  EventLoop _loop;     // 事件循环
};

#endif  // _TCPSERVER_H