/**
 * @brief http任务类
 */
#ifndef _HTTP_TASK_H
#define _HTTP_TASK_H

#include <iostream>

#include "ProtocolParser.h"
#include "TcpConnection.h"

enum TaskType {
  KEY_RECOMMAND = 0,   // 关键词推荐
  WEB_PAGE_SEARCH = 1  // 网页搜索
};

class HttpTask {
 public:
  /**
   * @brief 构造函数
   * @param conn 发起任务的连接
   * @param msg 待处理内容
   */
  HttpTask(TcpConnectionPtr conn, const string& msg)
      : _conn(std::move(conn)), _msg(std::move(msg)){};
  /**
   * @brief 任务处理函数
   * @note 处理客户端请求，将处理结果传给主线程，由主线程发送给客户端
   */
  virtual void process() = 0;

 protected:
  TcpConnectionPtr _conn;  // 发起任务的连接
  string _msg;             // 待处理内容
};

#endif  //_HTTP_TASK_H