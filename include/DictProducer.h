/**
 *  @brief 候选词推荐离线模块
 */

#ifndef _DICTPRODUCER_H
#define _DICTPRODUCER_H
#include <sstream>

#include "SplitToolCppJieba.h"

using std::istringstream;
using std::ofstream;
using std::pair;
class DictProducer {
 public:
  /**
   * @param tool  分词工具
   */
  DictProducer(SplitTool* tool);
  /**
   * @brief 创建词典
   * @param config  配置文件
   * @param stop_words  停用词集合
   */
  void buildDict(Configuration* config,
                 const unordered_set<string>& stop_words);

  /**
   * @brief 创建字符位置索引
   */
  void createIndex();

  /**
   * @brief 存储词典和字符位置索引
   * @param config  配置文件
   */
  void store(Configuration* config);

 private:
  /**
   * @brief 创建英文词典
   * @param en_corpus_path  英文语料文件/文件夹路径
   */
  void buildEnDict(const string& en_corpus_path);
  /**
   * @brief 创建中文词典
   * @param cn_corpus_path  中文语料文件/文件夹路径
   */
  void buildCnDict(const string& cn_corpus_path);

 private:
  vector<pair<string, int>> _dict;                   // 词典
  unordered_map<string, int> _freq_dict;             // 词频统计
  unordered_map<string, unordered_set<int>> _index;  // 字符位置索引
  SplitTool* _cuttor;                                // 分词工具
};

#endif  //_DICTPRODUCER_H