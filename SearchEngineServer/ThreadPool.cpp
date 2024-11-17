#include "ThreadPool.h"

ThreadPool::ThreadPool(size_t threads_num, size_t queue_size)
    : _threads_num(threads_num), _que(queue_size) {}

ThreadPool::~ThreadPool() {
  if (_alive) {
    stop();
  }
}

void ThreadPool::start() {
  _alive = true;
  _que.setAlive(true);
  for (size_t i = 0; i < _threads_num; ++i) {
    _threads.emplace_back(&ThreadPool::doTask, this);
  }
}

void ThreadPool::stop() {
  _alive = false;
  _que.setAlive(false);
  _que.notifyAll();
  for (auto& t : _threads) {
    t.join();
  }
}

void ThreadPool::addTask(ElemType task) {
  if (task != nullptr) _que.push(task);
}

ThreadPool::ElemType ThreadPool::getTask() { return _que.pop(); }

void ThreadPool::doTask() {
  while (_alive || !_que.empty()) {
    ElemType task = getTask();
    if (task != nullptr) {
      std::cout << std::this_thread::get_id() << " ";
      task();
    } else {
      std::cout << "Task is nullptr\n";
    }
  }
}