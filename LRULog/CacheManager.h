/**
 * @brief 缓存管理类
 */

#ifndef _CACHEMANAGER_H
#define _CACHEMANAGER_H

#include "LRUCache.h"

class CacheManager {
 public:
  void init(const string& filename);
  LRUCache& getCache(size_t index);
  void updateCache();

 private:
  vector<LRUCache> _caches;
};

#endif  //_CACHEMANAGER_H