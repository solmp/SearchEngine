/**
 * @brief 词典类(单例)
 */

#ifndef _DICTIONARY_H
#define _DICTIONARY_H

#include <queue>
#include <sstream>
#include <unordered_set>
#include <vector>

#include "CandidateResult.h"
#include "CommonTool.h"
#include "Configuration.h"

using std::istringstream;
using std::pair;
using std::priority_queue;
using std::unordered_set;
using std::vector;

class Dictionary : NonCopyable {
 public:
  static Dictionary* getInstance();

  /**
   * @brief 读取词典和字符位置索引
   * @param config 配置信息
   */
  void LoadDictionary(Configuration* config);
  /**
   * @brief 根据字符查找词典中的单词
   * @note 将查询结果插入到单词集合中，同时记录对应单词的频率
   * @param ch 待查询字符
   * @param words 单词集合
   * @param freq 单词频率
   */
  void doQuery(const string& ch, unordered_set<string>& words,
               unordered_map<string, size_t>& freq);

 private:
  static void destroy();

 private:
  static Dictionary* _pInstance;    // 单例对象指针
  vector<pair<string, int>> _dict;  // 词典：提供索引、单词、词频
  unordered_map<string, unordered_set<int>>
      _index;  // 位置索引：根据字符查找单词位置
};

#endif  //_DICTIONARY_H