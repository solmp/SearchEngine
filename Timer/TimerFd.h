/**
 * @brief 定时器类
 */
#ifndef __TIMERFD_H__
#define __TIMERFD_H__

#include <functional>

using std::function;

class TimerFd {
  using TimerFdCallback = function<void()>;

 public:
  TimerFd(TimerFdCallback &&cb, int initSec, int peridocSec);  //右值
  ~TimerFd();

  //启动与停止
  //使用IO多路复用进行监听
  void start();
  void stop();

  //创建用于通知的文件描述符
  int createTimerFd();

  //封装read
  void handleRead();

  //设置定时器
  void setTimerFd(int initSec, int peridocSec);

 private:
  int _tfd;             //用于通知的文件描述符
  TimerFdCallback _cb;  //被唤醒后执行的任务
  bool _isStarted;      //标识启动与否的标志
  int _initSec;         //定时器的起始时间
  int _peridocSec;      //定时器的间隔时间
};

#endif
