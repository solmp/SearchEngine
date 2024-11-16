/**
 * @brief 分词工具接口
 */

#ifndef _SPLITTOOL_H
#define _SPLITTOOL_H

#include <string>
#include <vector>

#include "NonCopyable.h"

using std::string;
using std::vector;
class SplitTool : NonCopyable {
 public:
  /**
   * @brief 对输入的字符串进行分词
   * @param str 输入的字符串
   * @param words 保存分词结果
   */
  virtual void cut(const string& str, vector<string>& words) = 0;
};

#endif  //_SPLITTOOL_H