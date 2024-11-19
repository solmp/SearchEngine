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
  string res = json_body.dump();
  // 将查询结果存入缓存
  CacheManager::getInstance()->addRecord(_sought, res);
  _conn->sendToLoop(
      std::bind(&TcpConnection::sendMsg, _conn, generateHttpResponse(res)));
}