/**
 * @brief Redis服务类
 */

#ifndef _REDISSERVER_H
#define _REDISSERVER_H

#include <sw/redis++/redis++.h>

#include "Configuration.h"
#include "NonCopyable.h"

using namespace sw::redis;
using std::string;

class RedisServer : NonCopyable {
 public:
  static RedisServer* getInstance();
  /**
   * @brief 设置Redis缓存
   * @param key 键
   * @param value 值
   */
  void set(const string& key, const std::string& value);
  /**
   * @brief 查询Redis缓存
   * @param key 键
   * @param value 值
   */
  bool query(const string& key, std::string& value);

 private:
  RedisServer();
  static void destroy();

 private:
  static RedisServer* instance;
  static const string redisDbName;  // Redis缓存数据库名称
  Redis _redis;                     // Redis对象
};

#endif  //_REDISSERVER_H