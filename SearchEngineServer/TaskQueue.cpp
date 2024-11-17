#include "TaskQueue.h"

void TaskQueue::push(ElemType task) {
  std::unique_lock<std::mutex> ul(_mutex);
  _notFull.wait(ul, [this]() { return !full(); });
  _que.push(task);
  _notEmpty.notify_one();
}

TaskQueue::ElemType TaskQueue::pop() {
  std::unique_lock<std::mutex> ul(_mutex);
  _notEmpty.wait(ul, [this]() { return !empty() || !_alive; });
  if (empty()) return nullptr;
  ElemType task = _que.front();
  _que.pop();
  _notFull.notify_one();
  return task;
}

bool TaskQueue::full() { return _que.size() >= _capacity; }

bool TaskQueue::empty() { return _que.empty(); }