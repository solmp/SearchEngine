#include <unistd.h>

#include <functional>
#include <iostream>
#include <thread>

#include "TimerFd.h"
#include "TimerTask.h"

using std::bind;
using std::thread;

void test() {
  TimerTask task;
  TimerFd tfd(bind(&TimerTask::process, &task), 1, 3);
  thread th(&TimerFd::start, &tfd);  // th线程作为A线程，主线程作为B线程
  //需要让主线程通知子线程th

  sleep(12);

  tfd.stop();
  th.join();
}

int main(int argc, char *argv[]) {
  test();
  return 0;
}
