/**
 * @brief 获取路径下所有文件
 */

#ifndef _DIRSCANNER_H
#define _DIRSCANNER_H

#include <filesystem>
#include <string>
#include <vector>

using std::string;
using std::vector;
class DirScanner {
 public:
  /**
   * @brief 获取所有文件路径
   */
  vector<string>& getFiles();
  /**
   * @brief 获取文件/文件夹下所有文件路径
   * @param path  文件/文件夹路径
   */
  void traversePath(const string& path);

 private:
  vector<string> _files;
};

#endif  //_DIRSCANNER_H