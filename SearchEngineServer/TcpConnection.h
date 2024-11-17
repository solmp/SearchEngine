/**
 * @brief Tcp连接类
 */
#ifndef _TCPCONNECTION_H
#define _TCPCONNECTION_H

#include <sys/socket.h>

#include <functional>
#include <memory>
#include <string>

#include "SocketIO.h"

using std::function;
using std::shared_ptr;
using std::string;

class EventLoop;
class TcpConnection;
using TcpConnectionPtr = shared_ptr<TcpConnection>;
using TcpConnectCallback = function<void(const TcpConnectionPtr&)>;
using FuncPtr = function<void()>;

#define MAX_BUF_SIZE 4096
/**
 * @note 继承std::enable_shared_from_this，用于在回调函数中使用shared_ptr
 */
class TcpConnection : public std::enable_shared_from_this<TcpConnection> {
 public:
  /**
   * @brief 构造函数
   * @param fd socket网络通信文件描述符
   * @param loop 事件循环
   */
  TcpConnection(int fd, EventLoop* loop) : _sockIO(fd), _loop(loop) {}
  /**
   * @brief 读取消息
   * @return string 读取到的消息
   */
  string readMsg();
  /**
   * @brief 发送消息
   * @param msg 待发送消息
   */
  void sendMsg(const string& msg);
  /**
   * @brief 判断对端是否关闭
   * @return bool 是否关闭
   */
  bool isClosed();
  /**
   * @brief 处理新连接
   * @note 回调_onNewConnection
   */
  void handleNewConnection();
  /**
   * @brief 处理消息
   * @note 回调_onMessage
   */
  void handleMessage();
  /**
   * @brief 处理关闭
   * @note 回调_onClose
   */
  void handleClose();
  /**
   * @brief 设置收到新连接的回调函数
   * @param cb 回调函数
   */
  void setNewConnectionCallback(const TcpConnectCallback& cb) {
    _onNewConnection = cb;
  }
  /**
   * @brief 设置收到消息的回调函数
   * @param cb 回调函数
   */
  void setMessageCallback(const TcpConnectCallback& cb) { _onMessage = cb; }
  /**
   * @brief 设置关闭连接的回调函数
   * @param cb 回调函数
   */
  void setCloseCallback(const TcpConnectCallback& cb) { _onClose = cb; }
  /**
   * @brief 将任务结果交给主线程，由主线程发送给客户端
   * @param cb 回调函数
   */
  void sendToLoop(FuncPtr&& cb);

 private:
  SocketIO _sockIO;                     // 用于socket网络通信
  TcpConnectCallback _onNewConnection;  // 新连接回调函数
  TcpConnectCallback _onMessage;        // 消息回调函数
  TcpConnectCallback _onClose;          // 关闭连接回调函数
  EventLoop* _loop;                     // 事件循环
};

#endif  //_TCPCONNECTION_H