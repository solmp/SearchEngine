/**
 * @brief 网页查询类(单例)
 */

#ifndef _WEBPAGEQUERY_H
#define _WEBPAGEQUERY_H

#include <queue>
#include <sstream>

#include "WebPage.h"

using std::istringstream;
using std::make_pair;
using std::priority_queue;

#define WEB_PAGE_SEARCH_NUM 10

class WebPageQuery : NonCopyable {
 public:
  static WebPageQuery* getInstance();
  /**
   * @brief 根据传入内容，查询相关网页
   * @param[in] key 查询关键词
   * @param[out] _webPages 查询结果
   */
  void doQuery(const string& key, vector<size_t>& _webPages);
  /**
   * @brief 根据id获取网页
   * @param[in] doc_id 网页id
   */
  WebPage getWebPage(size_t doc_id);

 private:
  WebPageQuery();
  static void destroy();
  void loadOffsetLib(const string& offsetLibPath);  // 加载去重网页偏移库
  void loadInvertIndexLib(const string& invertIndexLibPath);  // 加载倒排索引库

 private:
  static WebPageQuery* _pInstance;
  unordered_map<size_t, pair<off_t, size_t>> _offsetLib;  // 去重网页偏移库
  unordered_map<string, vector<pair<size_t, double>>>
      _invertIndexLib;                // 倒排索引库
  unordered_set<string> _stop_words;  // 停用词
  SplitTool* _wordCutTool;            // 分词工具
};

#endif  //_WEBPAGEQUERY_H