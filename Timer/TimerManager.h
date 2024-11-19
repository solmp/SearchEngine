/**
 * @brief 定时器管理类
 */

#ifndef _TIMER_MANAGER_H
#define _TIMER_MANAGER_H

#include <memory>
#include <thread>
#include <unordered_map>
#include <vector>

#include "TimerFd.h"
#include "TimerTask.h"

using std::bind;
using std::make_unique;
using std::thread;
using std::unique_ptr;
using std::unordered_map;

#define DEFAULT_INIT_SEC 1      // 默认的定时器起始时间
#define DEFAULT_PERIDOC_SEC 10  // 默认的定时器间隔时间

class TimerManager {
 public:
  /**
   * @param initSec 定时器的起始时间
   * @param peridocSec 定时器的间隔时间
   */
  TimerManager(int initSec = DEFAULT_INIT_SEC,
               int peridocSec = DEFAULT_PERIDOC_SEC);
  // 创建并运行所需的定时器
  void start();
  // 停止所有定时器
  void stop();
  // 添加定时任务
  void attach(TimerTask*);
  // 移除定时任务
  void detach(TimerTask*);

 private:
  int _timerfd;
  unordered_map<pthread_t, unique_ptr<TimerFd>> _wheelList;
  vector<thread> _timerThreads;
  int _initSec;
  int _peridocSec;
};

#endif  //_TIMER_MANAGER_H