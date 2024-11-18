/**
 * @brief 缓存管理类
 */

#ifndef _CACHEMANAGER_H
#define _CACHEMANAGER_H

#include "LRUCache.h"
#include "NonCopyable.h"

class CacheManager : NonCopyable {
 public:
  static CacheManager* getInstance();
  void init(const string& filename);
  LRUCache& getCache(size_t index);
  void updateCache();

 private:
  CacheManager();
  static void destroy();

 private:
  static CacheManager* _instance;
  vector<LRUCache> _caches;  // 缓存数组, 每个LRU对应线程
};

#endif  //_CACHEMANAGER_H