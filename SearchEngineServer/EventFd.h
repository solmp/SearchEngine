/**
 * @brief EventFd 通知事件的文件描述符类
 * @note 可实现线程间通信，框架中子线程执行任务后通知主线程返回响应给客户端
 */
#ifndef _EVENTFD_H
#define _EVENTFD_H

#include <sys/eventfd.h>
#include <sys/socket.h>
#include <unistd.h>

#include <iostream>

class EventFd {
 public:
  EventFd();
  ~EventFd() { close(_evfd); };
  /**
   * @brief 读取事件，主线程收到通知并处理
   */
  void handleRead();
  /**
   * @brief 写入事件，通知主线程
   */
  void wakeup();

  int fd() const { return _evfd; }

 private:
  int _evfd;
};

#endif  //_EVENTFD_H