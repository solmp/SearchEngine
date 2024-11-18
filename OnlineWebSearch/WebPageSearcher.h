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

#define WEB_PAGE_SEARCH_NUM 10

class WebPageSearcher {
 public:
  WebPageSearcher(const string& sought, const TcpConnectionPtr& conn)
      : _sought(sought), _conn(conn) {}
  void doQuery();
  void response();

 private:
  vector<WebPage> _webPages;
  string _sought;
  TcpConnectionPtr _conn;
};

#endif  //_WEBPAGESEARCHER_H