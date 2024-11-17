/**
 * @brief epoll封装类
 */
#ifndef _EPOLL_H
#define _EPOLL_H

#include <sys/epoll.h>
#include <unistd.h>

#include <iostream>
#include <vector>

using std::vector;

#define DEFAULT_EVENTS 1024   // 默认最大监听事件数量
#define DEFAULT_TIMEOUT 3000  // 默认epoll监听超时时间

class Epoll {
 public:
  Epoll() : _epfd(epoll_create1(0)), _events(DEFAULT_EVENTS) {
    if (_epfd == -1) {
      throw std::runtime_error("epoll_create1 error");
    }
  }
  ~Epoll() { close(_epfd); }
  /**
   * @brief 添加监听事件
   * @param fd 待监听事件文件描述符
   * @param events 监听事件类型
   */
  void addEvent(int fd, EPOLL_EVENTS events = EPOLLIN);
  /**
   * @brief 删除监听事件
   * @param fd 待删除事件文件描述符
   */
  void delEvent(int fd);
  /**
   * @brief 开始监听
   * @param timeout 监听超时时间
   * @return int 就绪事件数量
   */
  int epollWait(int timeout = DEFAULT_TIMEOUT);

  /**
   * @brief 获取就绪事件
   * @param idx 就绪事件下标
   * @return struct epoll_event 就绪事件
   */
  struct epoll_event getReadyEvent(size_t idx) const {
    return _events[idx];
  }

 private:
  int _epfd;
  vector<struct epoll_event> _events;  // 就绪事件数组
};

#endif  //_EPOLL_H