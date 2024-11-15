/**
 * @brief 预处理网页库
 */

#ifndef _PAGELIBPREPROCESSOR_H
#define _PAGELIBPREPROCESSOR_H

#include <unordered_map>

#include "WebPage.h"
#include "simhash/Simhasher.hpp"

using simhash::Simhasher;
using std::pair;
using std::unordered_map;

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
   * @brief 去重网页，生成去重网页库和去重网页偏移库
   */
  void cutRedundantPage();

  void bulidInvertIndexMap();

  void storeOnDisk();

 private:
  /**
   * @brief 读取未去重的网页偏移库
   */
  void readOldOffsetLib();

 private:
  unordered_map<size_t, pair<off_t, size_t>> _offsetLib;  // 去重网页偏移库
  // 倒排索引<单词，<文档编号，权重>>
  unordered_map<string, pair<size_t, double>> _invertIndexLib;
  Configuration* _conf;    // 配置文件
  SplitTool* _wordCutter;  // 分词工具
};

#endif  //_PAGELIBPREPROCESSOR_H