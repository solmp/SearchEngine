/**
 * @brief 缓存管理类
 */

#ifndef _CACHEMANAGER_H
#define _CACHEMANAGER_H

#include "LRUCache.h"
#include "NonCopyable.h"
#include "RedisServer.h"

class CacheManager : NonCopyable {
 public:
  static CacheManager* getInstance();
  /**
   * @brief 查询公共缓存
   */
  bool queryPublicCache(const string& key, string& value);
  /**
   * @brief 添加公共缓存
   */
  void addPublicCache(const string& key, const string& value);

  // void init(const string& filename);
  // LRUCache& getCache(size_t index);
  // void updateCache();

 private:
  CacheManager();
  static void destroy();

 private:
  static CacheManager* _instance;
  vector<LRUCache> _caches;  // 缓存数组, 每个LRU对应线程
  mutex _mutex;              // 互斥锁
};

#endif  //_CACHEMANAGER_H