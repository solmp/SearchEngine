/**
 * @brief http任务类
 */
#ifndef _HTTP_TASK_H
#define _HTTP_TASK_H

#include <iostream>

#include "ProtocolParser.h"
#include "TcpConnection.h"

using std::cout;
using std::endl;

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
  void process() {
    ProtocolParser parser;                      // 创建解析器
    parser.doParse(_msg);                       // 解析http请求
    http_struct http_req = parser.getResult();  // 获取解析结果
    http_req.print();                           // 打印http请求
    // TODO：1.关键词推荐结果
    // TODO：2.网页搜索结果
    // body：json 格式
    string resp =
        "HTTP/1.1 200 OK\r\n"
        "Server: nginx\r\n"
        "content-length: 11\r\n"
        "\r\n"
        "hello:world\r\n"
        "\r\n";
    _conn->sendToLoop(std::bind(&TcpConnection::sendMsg, _conn, resp));
  }

 private:
  TcpConnectionPtr _conn;
  string _msg;
};

#endif  //_HTTP_TASK_H