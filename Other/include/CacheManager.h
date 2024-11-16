/**
 * Project SearchEngine
 */

#ifndef _CACHEMANAGER_H
#define _CACHEMANAGER_H

class CacheManager {
 public:
  /**
   * @param filename
   */
  void init(string filename);

  /**
   * @param int
   */
  LRUCache &getCache(void int);

  void updateCache();

 private:
  vector<LRUCache> _caches;
};

#endif  //_CACHEMANAGER_H