/**
 * @brief 任务队列类
 */
#ifndef _TASKQUEUE_H
#define _TASKQUEUE_H

#include <condition_variable>
#include <functional>
#include <mutex>
#include <queue>

#include "HttpTask.h"
using std::condition_variable;
using std::function;
using std::mutex;
using std::queue;

class TaskQueue {
  using ElemType = function<void()>;

 public:
  /**
   * @brief 构造函数
   * @param capacity 任务队列容量
   */
  TaskQueue(size_t capacity) : _capacity(capacity) {}
  /**
   * @brief 添加任务
   * @param task 任务
   */
  void push(ElemType task);
  /**
   * @brief 取出任务
   * @return 任务
   */
  ElemType pop();
  /**
   * @brief 任务队列判满
   */
  bool full();
  /**
   * @brief 任务队列判空
   */
  bool empty();
  /**
   * @brief 设置任务队列状态
   * @param alive 是否存活
   * @note 使得在停止线程池时，不再阻塞等待任务的入队和出队
   */
  void setAlive(bool alive) {
    std::unique_lock<std::mutex> ul(_mutex);  // 加锁，防止误判虚假唤醒
    _alive = alive;
  }
  /**
   * @brief 唤醒所有线程
   */
  void notifyAll() { _notEmpty.notify_all(); }

 private:
  size_t _capacity;              // 任务队列容量
  queue<ElemType> _que;          // 任务队列
  mutex _mutex;                  // 互斥锁，维护任务队列
  condition_variable _notFull;   // 非满条件变量
  condition_variable _notEmpty;  // 非空条件变量
  bool _alive = false;           // 任务队列状态
};

#endif  //_TASKQUEUE_H