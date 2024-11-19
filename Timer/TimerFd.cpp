#include "TimerFd.h"

TimerFd::TimerFd(TimerFdCallback &&cb, int initSec, int peridocSec)
    : _tfd(timerfd_create(CLOCK_REALTIME, 0)),
      _cb(std::move(cb)),
      _isStarted(false),
      _initSec(initSec),
      _peridocSec(peridocSec) {}

TimerFd::~TimerFd() {
  stop();
  close(_tfd);
}

void TimerFd::start() {
  struct pollfd pfd;
  pfd.events = POLLIN;
  pfd.fd = _tfd;  // 监听用于通知的文件描述符
  // 启动定时器
  setTimerFd(_initSec, _peridocSec);

  _isStarted = true;
  while (_isStarted) {
    int nready = poll(&pfd, 1, 5000);
    if (-1 == nready && errno == EINTR) {
      continue;
    } else if (-1 == nready) {
      fprintf(stderr, "poll error\n");
    } else if (0 == nready) {
      fprintf(stderr, "poll timeout\n");
    } else {
      if (pfd.revents & POLLIN) {
        handleRead();
      }
    }
  }
}

void TimerFd::stop() {
  if (_isStarted) {
    _isStarted = false;
    setTimerFd(0, 0);  // 停止定时器
  }
}

void TimerFd::handleRead() {
  uint64_t one = 1;
  ssize_t ret = read(_tfd, &one, sizeof(uint64_t));
  if (ret != sizeof(uint64_t)) {
    perror("handleRead");
  }
  if (_cb) {
    _cb();  //执行的事件
  }
}

void TimerFd::setTimerFd(int initSec, int peridocSec) {
  struct itimerspec newValue;

  newValue.it_value.tv_sec = initSec;  // 起始时间
  newValue.it_value.tv_nsec = 0;

  newValue.it_interval.tv_sec = peridocSec;  // 时间间隔
  newValue.it_interval.tv_nsec = 0;

  int ret = timerfd_settime(_tfd, 0, &newValue, nullptr);
  if (ret < 0) {
    perror("setTimerFd");
    return;
  }
}
