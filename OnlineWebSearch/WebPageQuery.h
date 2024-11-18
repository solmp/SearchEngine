/**
 * @brief 网页查询类(单例)
 */

#ifndef _WEBPAGEQUERY_H
#define _WEBPAGEQUERY_H

#include "WebPage.h"

class WebPageQuery : NonCopyable {
 public:
  static WebPageQuery* getInstance();
  void doQuery(const string& key, vector<WebPage>& _webPages);

 private:
  WebPageQuery();
  static void destroy();
  // void loadOffsetLib(const string& offsetLibPath);
  // void loadInvertIndexLib(const string& invertIndexLibPath);
  // void loadPageLib(const string& pageLibPath);
  // void loadStopWordList(const string& stopWordList);

 private:
  static WebPageQuery* _pInstance;
  vector<WebPage> _pages;
  unordered_map<int, pair<int, int>> _offsetlib;
  unordered_map<int, pair<int, double>> _invertIndexLib;
  SplitTool* _wordCutTool;
};

#endif  //_WEBPAGEQUERY_H