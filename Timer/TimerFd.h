/**
 * @brief 定时器类
 */
#ifndef __TIMERFD_H__
#define __TIMERFD_H__

#include <poll.h>
#include <sys/timerfd.h>
#include <unistd.h>

#include <cstdint>
#include <functional>
#include <iostream>

using std::function;

class TimerFd {
  using TimerFdCallback = function<void()>;

 public:
  /**
   * @param cb 定时器到期后执行的任务
   * @param initSec 定时器的起始时间
   * @param peridocSec 定时器的间隔时间
   */
  TimerFd(TimerFdCallback &&cb, int initSec, int peridocSec);
  ~TimerFd();
  void start();
  void stop();

  // 接收并处理定时器事件
  void handleRead();

  // 设置定时器
  void setTimerFd(int initSec, int peridocSec);

 private:
  int _tfd;             // 用于通知的文件描述符
  TimerFdCallback _cb;  // 被唤醒后执行的任务
  bool _isStarted;      // 标识启动与否的标志
  int _initSec;         // 定时器的起始时间
  int _peridocSec;      // 定时器的间隔时间
};

#endif  //__TIMERFD_H__
