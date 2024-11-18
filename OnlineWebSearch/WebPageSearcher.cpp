#include "WebPageSearcher.h"

void WebPageSearcher::doQuery() {
  WebPageQuery* webPageQuery = WebPageQuery::getInstance();
  webPageQuery->doQuery(_sought, _webPages);
}

void WebPageSearcher::response() {
  // 将结果包装为json格式返回给客户端
  size_t size = _webPages.size();
  json json_body = {
      {"size", size},
      {"result", json::array()},
  };

  for (auto& doc_id : _webPages) {
    WebPage page = WebPageQuery::getInstance()->getWebPage(doc_id);
    json_body["result"].push_back(page.toJson());
  }
  // 将查询结果存入Redis缓存
  RedisServer::getInstance()->set(_sought, json_body.dump());
  string response = generateHttpResponse(json_body.dump());
  _conn->sendToLoop(std::bind(&TcpConnection::sendMsg, _conn, response));
}