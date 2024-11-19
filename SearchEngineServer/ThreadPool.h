/**
 * @brief 线程池类
 */
#ifndef _THREADPOOL_H
#define _THREADPOOL_H
#include <iostream>
#include <list>
#include <thread>

#include "CacheManager.h"
#include "TaskQueue.h"

using std::list;
using std::thread;

#define DEFAULT_THREADS_NUM 4  // 默认线程数量
#define DEFAULT_QUEUE_SIZE 10  // 默认任务队列大小

class ThreadPool {
  using ElemType = function<void()>;

 public:
  ThreadPool(size_t threads_num = DEFAULT_THREADS_NUM,
             size_t queue_size = DEFAULT_QUEUE_SIZE);
  ~ThreadPool();
  // 启动线程池
  void start();
  // 停止线程池
  void stop();
  // 添加任务到任务队列
  void addTask(ElemType task);

 private:
  // 从任务队列中获取一个任务
  ElemType getTask();
  // 线程执行任务
  void doTask();

 private:
  size_t _threads_num;    // 线程数量
  list<thread> _threads;  // 线程列表
  TaskQueue _que;         // 任务队列
  bool _alive = false;    // 线程池状态
};

#endif  //_THREADPOOL_H