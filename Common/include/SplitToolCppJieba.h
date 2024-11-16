/**
 * @brief 使用cppjieba分词工具，对中英文文本进行分词
 */

#ifndef _SPLITTOOLCPPJIEBA_H
#define _SPLITTOOLCPPJIEBA_H

#include <unordered_set>

#include "Configuration.h"
#include "DirScanner.h"
#include "SplitTool.h"
#include "cppjieba/Jieba.hpp"

using std::unordered_set;

class SplitToolCppJieba : public SplitTool {
 public:
  SplitToolCppJieba(json& config)
      : _jieba(config["DICT_PATH"], config["HMM_PATH"],
               config["USER_DICT_PATH"], config["IDF_PATH"],
               config["STOP_WORD_PATH"]) {}

  void cut(const string& str, vector<string>& words) override {
    _jieba.Cut(str, words, true);
  }

 private:
  cppjieba::Jieba _jieba;  // jieba 分词工具
};

/**
 * @brief 获取停用词集合
 * @param stop_words_path  停用词所在文件/文件夹路径
 * @param files 文件路径集合
 */
void LoadStopWords(const string& stop_words_path,
                   unordered_set<string>& stop_words);

/**
 * @brief 计算字符所占字节数
 * @param ch 字符
 */
size_t nBytesCode(const char ch);

#endif  //_SPLITTOOLCPPJIEBA_H