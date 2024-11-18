#include "WebPageQuery.h"

WebPageQuery* WebPageQuery::_pInstance = nullptr;

WebPageQuery::WebPageQuery() {
  // TODO
  // cppjieba转单例，获取分词工具和其它数据（倒排索引、停用词、去重网页偏移库）
}
WebPageQuery* WebPageQuery::getInstance() {
  if (_pInstance == nullptr) {
    atexit(destroy);
    _pInstance = new WebPageQuery();
  }
  return _pInstance;
}

void WebPageQuery::destroy() {
  if (_pInstance) {
    delete _pInstance;
  }
}

void WebPageQuery::doQuery(const string& key, vector<WebPage>& _webPages) {
  // TODO
  // 句子 -> 分词 -> 过滤停用词 -> 返回结果集交集（需要排序）
  // 排序：余弦相似算法+优先队列
}