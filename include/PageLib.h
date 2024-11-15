/**
 * @brief 网页库类
 * @note 用于读取语料生成网页库和网页偏移库
 */

#ifndef _PAGELIB_H
#define _PAGELIB_H

#include "DirScanner.h"
#include "WebPage.h"

class PageLib {
 public:
  /**
   * @brief 构造函数
   * @param config 配置文件
   */
  PageLib(Configuration* config);
  /**
   * @brief 创建网页库
   */
  void create();

  /**
   * @保存网页库索引
   */
  void store();

 private:
  Configuration* _config;     // 配置文件
  vector<string> _pagesPath;  // 语料库中的所有xml文件路径
  unordered_map<size_t, pair<off_t, size_t>> _offsetLib;  // 文章id、偏移量和文章大小
};

#endif  //_PAGELIB_H