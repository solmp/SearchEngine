#include "TimerManager.h"

TimerManager::TimerManager(int initSec, int peridocSec)
    : _initSec(initSec), _peridocSec(peridocSec) {}

void TimerManager::start() {
  // 增加所需定时器
  attach(new TimerTask());  // 主线程定时器，用来增量同步LRU缓存
  // 创建定时器线程
  _timerThreads.reserve(_wheelList.size());
  for (auto& it : _wheelList) {
    _timerThreads.emplace_back(&TimerFd::start, it.second.get());
  }
}

void TimerManager::stop() {
  for (auto& it : _wheelList) {
    it.second->stop();
  }
  for (auto& it : _timerThreads) {
    if(it.joinable()) {
      it.join();
    }
  }
  fprintf(stdout, "Timer stoped\n");
}

void TimerManager::attach(TimerTask* task) {
  _wheelList.emplace(pthread_self(),
                     make_unique<TimerFd>(bind(&TimerTask::process, task),
                                          _initSec, _peridocSec));
}

void TimerManager::detach(TimerTask* task) { _wheelList.erase(pthread_self()); }
