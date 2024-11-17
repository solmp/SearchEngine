/**
 * @brief 网页查询类
 */

#ifndef _WEBPAGEQUERY_H
#define _WEBPAGEQUERY_H

#include "WebPage.h"

class WebPageQuery {
 public:
  WebPageQuery();

  /**
   * @param key
   */
  string doQuery(string key);

 private:
  vector<WebPage> _pages;
  unordered_map<int, pair<int, int>> _offsetlib;
  unordered_map<int, pair<int, double>> _invertIndexLib;
  SplitTool* _wordCutTool;
};

#endif  //_WEBPAGEQUERY_H