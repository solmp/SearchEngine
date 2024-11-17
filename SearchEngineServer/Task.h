/**
 * @brief 任务类
 */
#ifndef _TASK_H
#define _TASK_H

#include <iostream>

#include "TcpConnection.h"

using std::cout;
using std::endl;

class Task {
 public:
  /**
   * @brief 构造函数
   * @param conn 发起任务的连接
   * @param msg 待处理内容
   */
  Task(TcpConnectionPtr conn, const string& msg)
      : _conn(std::move(conn)), _msg(std::move(msg)){};
  /**
   * @brief 任务处理函数
   * @note 处理客户端请求，将处理结果传给主线程，由主线程发送给客户端
   */
  void process() {
    cout << "server receive msg: " << _msg << endl;
    string resp = "server resp: " + _msg;
    _conn->sendToLoop(std::bind(&TcpConnection::sendMsg, _conn, resp));
  }

 private:
  TcpConnectionPtr _conn;
  string _msg;
};

#endif  //_TASK_H