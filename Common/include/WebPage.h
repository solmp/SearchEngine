/**
 * @brief 网页类
 */

#ifndef _WEBPAGE_H
#define _WEBPAGE_H

#include <regex>
#include <set>

#include "SplitToolCppJieba.h"
#include "tinyxml2.h"
using std::ofstream;
using std::pair;
using std::regex;

using std::set;
using tinyxml2::XMLDocument;
using tinyxml2::XMLElement;
using tinyxml2::XMLNode;
using tinyxml2::XMLText;

class WebPage {
 public:
  WebPage(XMLElement* item, size_t doc_id);
  /**
   * @brief 获取文档id
   */
  int getDocId() const { return _docId; };
  /**
   * @brief 获取文档标题
   */
  string getTile() const { return _docTitle; }
  /**
   * @brief 获取文档大小
   */
  size_t getDocSize() const { return _docSize; }
  /**
   * @brief 获取文档内容
   */
  string getDocContent() const { return _docContent; }

  /**
   * @brief 格式化文档进行处理
   */
  void processDoc();
  /**
   * @brief 将文档转换为json格式
   */
  json toJson();

  /**
   * @brief 获取文档的词频统计map
   */
  // TODO:  unordered_map<string, int>& getWordsMap();
  /**
   * @brief TODO: 获取文档的topk词集
   */
  // TODO:  void calcTopK(vector<string>& wordsVec, int k, set<string>& stopWordList);

  /**
   * @brief 将文档写入文件
   * @param ofs: 文件输出流
   */
  void dump(ofstream& ofs);

  /**
   * @brief 判断两篇文档是否相等
   */
  //   friend bool operator==(const WebPage& lhs, const WebPage& rhs);

  /**
   * @brief 重载<运算符, 用于set容器排序
   * @param lhs: 左操作数
   * @param rhs: 右操作数
   * @note 根据文档id进行排序
   */
  friend bool operator<(const WebPage& lhs, const WebPage& rhs);

 private:
  /**
   * @brief 解码 HTML 实体
   * @param input: 待处理的字符串
   */
  string decodeHtmlEntities(const string& input);

 private:
  XMLElement* _doc;     // 整篇文档，包含xml在内
  size_t _docId;        // 文档id
  string _docTitle;     // 文档标题
  string _docUrl;       // 文档URL
  string _docContent;   // 文档内容
  size_t _docSize = 0;  // 文档大小
};

/**
 * @brief 去除头尾空格、制表符、回车、换行符
 */
void trim(string& str);

#endif  //_WEBPAGE_H