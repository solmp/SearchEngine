/**
 * @brief 网页搜索离线模块，用于预处理网页库
 * @note 读取网页库和网页偏移库，去重后生成去重网页库、去重网页偏移库、倒排索引并保存
 */

#ifndef _PAGELIBPREPROCESSOR_H
#define _PAGELIBPREPROCESSOR_H

#include <unordered_map>

#include "WebPage.h"
#include "simhash/Simhasher.hpp"

using simhash::Simhasher;
using std::pair;

#define TOP_N 5  // 关键词个数
class PageLibPreprocessor {
 public:
  /**
   * @brief 构造函数
   * @param config: 配置文件
   * @param tool: 分词工具
   */
  PageLibPreprocessor(Configuration* config, SplitTool* tool);

  /**
   * @brief 去重网页，生成去重网页库和去重网页偏移库，并保存到磁盘
   */
  void cutRedundantPage();

  /**
   * @brief 生成倒排索引
   * @param stop_words: 停用词集合
   */
  void bulidInvertIndexMap(unordered_set<string>& stop_words);

  /**
   * @brief 保存倒排索引到磁盘
   */
  void storeOnDisk();

 private:
  /**
   * @brief 读取网页偏移库
   */
  void readOldOffsetLib(const string& page_offset_path);

 private:
  unordered_map<size_t, pair<off_t, size_t>> _offsetLib;  // 网页偏移库
  // 倒排索引<单词，<文档编号，权重>>
  unordered_map<string, vector<pair<size_t, double>>> _invertIndexLib;
  Configuration* _conf;    // 配置文件
  SplitTool* _wordCutter;  // 分词工具
};

#endif  //_PAGELIBPREPROCESSOR_H