/**
 * @brief 定时任务类
 */

#ifndef _TIMERTASK_H
#define _TIMERTASK_H

#include "CacheManager.h"
class TimerTask {
 public:
  void process() {
    CacheManager::getInstance()->updateThreadLRUCaches();
  }
};

#endif  //_TIMERTASK_H