/**
 * @brief 网页搜索在线模块
 */

#ifndef _WEBPAGESEARCHER_H
#define _WEBPAGESEARCHER_H

#include <string>

#include "ProtocolParser.h"
#include "TcpConnection.h"
#include "WebPageQuery.h"

using std::string;

class WebPageSearcher {
 public:
  WebPageSearcher(const string& sought, const TcpConnectionPtr& conn)
      : _sought(sought), _conn(conn) {}
  // 根据传入内容，查询相关网页
  void doQuery();
  // 将查询结果交给主线程，准备发送响应
  void response();

 private:
  vector<size_t> _webPages;  // 查询结果
  string _sought;            // 查询关键词
  TcpConnectionPtr _conn;    // Tcp连接
};

#endif  //_WEBPAGESEARCHER_H