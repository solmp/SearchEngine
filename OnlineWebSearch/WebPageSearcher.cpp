#include "WebPageSearcher.h"

void WebPageSearcher::doQuery() {
  WebPageQuery* webPageQuery = WebPageQuery::getInstance();
  webPageQuery->doQuery(_sought, _webPages);
}

void WebPageSearcher::response() {
  // 将结果包装为json格式返回给客户端
  size_t size = _webPages.size() < WEB_PAGE_SEARCH_NUM ? _webPages.size()
                                                       : WEB_PAGE_SEARCH_NUM;
  json json_body = {
      {"size", size},
      {"result", json::array()},
  };

  for (auto& page : _webPages) {
    json_body["result"].push_back(page.toJson());
  }
  string response = generateHttpResponse(json_body.dump());
  _conn->sendToLoop(std::bind(&TcpConnection::sendMsg, _conn, response));
}