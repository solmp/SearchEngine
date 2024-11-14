/**
 * @brief 读取配置文件
 */

#ifndef _CONFIGURATION_H
#define _CONFIGURATION_H

#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <string>
#include <unordered_map>

#include "Noncopyable.h"

using nlohmann::json;
using std::ifstream;
using std::string;
using std::unordered_map;

enum ConfigCategory {
  SPLIT_TOOL = 0,  // 分词工具相关配置
  OTHER            // 其他配置
};

class Configuration : Noncopyable {
 public:
  /**
   * @brief 获取单例对象
   * @return Configuration* 单例对象指针
   */
  static Configuration* getInstance();
  /**
   * @brief 读取配置文件
   * @param configFilePath 配置文件路径
   */
  void LoadConfig(const string& configFilePath);
  /**
   * @brief 获取配置信息
   * @param category 配置类别
   * @return json 配置信息
   */
  json& getConfigMap(const ConfigCategory category);

 private:
  /**
   * @brief 回收单例对象
   */
  static void destroy();
  /**
   * @brief 选择配置类别
   * @param category 配置类别
   */
  ConfigCategory chooseCategory(const string& category);

 private:
  static Configuration* _pInstance;              // 单例对象指针
  unordered_map<ConfigCategory, json> _configs;  // 配置信息
};

#endif  //_CONFIGURATION_H