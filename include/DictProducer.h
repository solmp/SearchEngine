/**
 *  @brief 候选词推荐离线模块
 */

#ifndef _DICTPRODUCER_H
#define _DICTPRODUCER_H
#include "SplitToolCppJieba.h"

using std::ofstream;
using std::pair;
class DictProducer {
 public:
  /**
   * @param corpus_path  语料文件路径，可以是文件或者目录
   * @param tool  分词工具
   */
  DictProducer(const string& corpus_path, SplitTool* tool);

  /**
   * @brief 创建词典
   * @param stop_words 停用词集合
   */
  void buildDict(const unordered_set<string>& stop_words);

  /**
   * @brief 创建字符位置索引
   * @param stop_words 停用词集合
   */
  void createIndex();

  /**
   * @brief 存储词典和字符位置索引
   * @param dict_path  词典存储路径
   * @param charIndex_path  字符位置索引存储路径
   */
  void store(const string& dict_path, const string& charIndex_path);

 private:
  vector<string> _files;                             // 语料文件路径
  vector<pair<string, int>> _dict;                   // 词典
  unordered_map<string, unordered_set<int>> _index;  // 字符位置索引
  SplitTool* _cuttor;                                // 分词工具
};

#endif  //_DICTPRODUCER_H