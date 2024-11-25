/**
 * @brief Redis服务类
 */

#ifndef _REDISSERVER_H
#define _REDISSERVER_H

#include <sw/redis++/redis++.h>

#include "Configuration.h"

using namespace sw::redis;
using std::string;

class RedisServer : NonCopyable {
 public:
  static RedisServer* getInstance();
  /**
   * @brief 设置Redis缓存
   */
  void addRecord(const string& key, const std::string& value);
  /**
   * @brief 查询Redis缓存
   */
  bool query(const string& key, std::string& value);
  // 检查redis连接状态
  bool checkConnect();

 private:
  RedisServer();
  static void destroy();

 private:
  static RedisServer* instance;
  static const string redisDbName;  // Redis缓存数据库名称
  Redis _redis;                     // Redis对象
};

#endif  //_REDISSERVER_H