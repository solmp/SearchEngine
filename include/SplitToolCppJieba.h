/**
 * @brief 使用cppjieba分词工具，对中英文文本进行分词
 */

#ifndef _SPLITTOOLCPPJIEBA_H
#define _SPLITTOOLCPPJIEBA_H

#include "Configuration.h"
#include "SplitTool.h"
#include "cppjieba/Jieba.hpp"

class SplitToolCppJieba : public SplitTool {
 public:
  SplitToolCppJieba(json config)
      : _jieba(config["DICT_PATH"], config["HMM_PATH"],
               config["USER_DICT_PATH"], config["IDF_PATH"],
               config["STOP_WORD_PATH"]) {}

  void cut(const string& str, vector<string>& words) override {
    _jieba.Cut(str, words, true);
  }

 private:
  cppjieba::Jieba _jieba;  // jieba 分词工具
};
#endif  //_SPLITTOOLCPPJIEBA_H