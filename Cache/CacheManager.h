/**
 * @brief 缓存管理类
 */

#ifndef _CACHEMANAGER_H
#define _CACHEMANAGER_H

#include <memory>

#include "LRUCache.h"
#include "RedisServer.h"

using std::shared_ptr;

#define LRU_CACHE_SIZE 5
class CacheManager : NonCopyable {
 public:
  static CacheManager* getInstance();
  /**
   * @brief 查询缓存
   */
  bool queryRecord(const string& key, string& value);
  /**
   * @brief 添加缓存
   */
  void addRecord(const string& key, const string& value);
  /**
   * @brief 添加线程LRU缓存
   * @param tid 线程ID
   */
  void addThreadLRUCache(const pthread_t tid);
  /**
   * @brief 更新线程LRU缓存
   */
  void updateThreadLRUCaches();
  /**
   * @brief 保存公共缓存
   */
  void storePublicCache() {
    _publicCache.store();
    fprintf(stdout, "cache stored\n");
  };

 private:
  CacheManager();
  static void destroy();

 private:
  static CacheManager* _instance;
  // LRU 缓存数组, 每个LRU对应一个线程
  unordered_map<pthread_t, shared_ptr<LRUCache>> _caches;
  // 待更新的LRU缓存
  unordered_map<pthread_t, shared_ptr<LRUCache>> _caches_pending;
  unordered_map<pthread_t, mutex> _mutexs;  // 线程互斥锁
  LRUCache _publicCache;                    // 公共LRU缓存
  mutex _mutex;                             // 公共互斥锁
};

#endif  //_CACHEMANAGER_H