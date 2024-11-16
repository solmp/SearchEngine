/**
 * Project SearchEngine
 */

#ifndef _WEBPAGEQUERY_H
#define _WEBPAGEQUERY_H

class WebPageQuery {
 public:
  void WebPageQuery();

  /**
   * @param key
   */
  string doQuery(string key);

 private:
  vector<WebPage> _pages;
  unordered_map<int, pair<int, int>> _offsetlib;
  unordered_map<int, pair<int, double>> _invertIndexLib;
  SplitTool _wordCutTool;
};

#endif  //_WEBPAGEQUERY_H