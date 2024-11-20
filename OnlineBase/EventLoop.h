/**
 * @brief 事件循环类
 */
#ifndef _EVENTLOOP_H
#define _EVENTLOOP_H

#include <sys/eventfd.h>

#include <mutex>
#include <unordered_map>

#include "Acceptor.h"
#include "Epoll.h"
#include "EventFd.h"
#include "TcpConnection.h"
#include "TimerManager.h"

using std::lock_guard;
using std::mutex;
using std::unordered_map;

class EventLoop {
 public:
  EventLoop(Acceptor& acceptor) : _acceptor(acceptor) {
    _epoll.addEvent(_acceptor.fd());  // 添加服务器监听文件描述符
    _epoll.addEvent(_eventfd.fd());   // 添加通知事件文件描述符
    _epoll.addEvent(STDIN_FILENO);    // 添加标准输入文件描述符
  }
  /**
   * @brief 启动事件循环
   */
  void loop();
  /**
   * @brief 退出事件循环
   */
  void unloop() {
    _timer.stop();
    _isLooping = false;
    CacheManager::getInstance()->storePublicCache();
  }
  /**
   * @brief 处理新连接
   */
  void handleNewConnection();
  /**
   * @brief 处理消息
   * @param peerfd 客户端文件描述符
   */
  void handleMessage(int peerfd);
  /**
   * @brief 处理客户端断开连接事件
   * @param peerfd 客户端文件描述符
   */
  void handleClose(int peerfd);
  /**
   * @brief 添加新连接回调函数
   * @param cb 回调函数
   */
  void setNewConnectionCallback(TcpConnectCallback&& cb) {
    _onNewConnection = std::move(cb);
  }
  /**
   * @brief 添加消息回调函数
   * @param cb 回调函数
   */
  void setMessageCallback(TcpConnectCallback&& cb) {
    _onMessage = std::move(cb);
  }
  /**
   * @brief 添加客户端断开连接回调函数
   * @param cb 回调函数
   */
  void setCloseCallback(TcpConnectCallback&& cb) { _onClose = std::move(cb); }
  /**
   * @brief 子线程将要返回的响应内容交给主线程
   * @param cb 回调函数
   * @note 子线程完成任务后，将要返回的响应内容保存至主线程的_pending中
   */
  void readInLoop(FuncPtr&& cb);
  /**
   * @brief 处理结果
   * @note 用于处理_pending中，要返回给客户端的响应内容
   */
  void dealResult();

 private:
  bool _isLooping;      // 控制事件循环是否退出
  Epoll _epoll;         // epoll监听类
  EventFd _eventfd;     // 通知事件文件描述符
  Acceptor& _acceptor;  // 服务器监听类
  unordered_map<int, shared_ptr<TcpConnection>> _conns;  // 客户端连接集合
  TcpConnectCallback _onNewConnection;  // 新连接回调函数
  TcpConnectCallback _onMessage;        // 消息回调函数
  TcpConnectCallback _onClose;          // 客户端断开连接回调函数
  mutex _mutex;                         // 互斥锁，用于维护_pending
  vector<FuncPtr> _pending;             // 待处理的响应任务
  TimerManager _timer;                  // 定时器
};

#endif  //_EVENTLOOP_H