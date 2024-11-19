#include "CacheManager.h"

CacheManager* CacheManager::_instance = getInstance();

CacheManager* CacheManager::getInstance() {
  if (_instance == nullptr) {
    atexit(destroy);
    _instance = new CacheManager();
  }
  return _instance;
}

CacheManager::CacheManager() : _publicCache(LRU_CACHE_SIZE) {}

void CacheManager::destroy() {
  if (_instance) {
    delete _instance;
    _instance = nullptr;
  }
}

bool CacheManager::queryRecord(const string& key, string& value) {
  unique_lock<mutex> lock(_mutex);
  // 1.查询线程LRU缓存
  if (_caches[pthread_self()]->getRecord(key, value)) return true;
  // 2.查询Redis缓存
  RedisServer* redis = RedisServer::getInstance();
  if (redis->checkConnect() && redis->query(key, value)) return true;
  return false;
}

void CacheManager::addRecord(const string& key, const string& value) {
  unique_lock<mutex> lock(_mutex);
  // 0.添加公共LRU缓存
  _publicCache.addRecord(key, value);
  // 1.添加线程LRU缓存
  _caches[pthread_self()]->addRecord(key, value);
  // 2.添加Redis缓存
  RedisServer* redis = RedisServer::getInstance();
  if (redis->checkConnect()) redis->addRecord(key, value);
}

void CacheManager::addThreadLRUCache(const pthread_t pid) {
  std::lock_guard<std::mutex> lock(_mutex);
  _caches.emplace(pid, std::make_unique<LRUCache>(LRU_CACHE_SIZE));
}

void CacheManager::updateThreadLRUCaches() {
  // 更新主LRU缓存：将线程池中线程的pending缓存合并到主LRU缓存中
  fprintf(stdout, ">>CacheManager::updateThreadLRUCaches\n");
  for (auto& cache : _caches) {
    list<std::pair<string, string>> pending;
    {
      std::lock_guard<std::mutex> lock(_mutex);
      pending.swap(cache.second->getPending());
    }
    for (auto& record : pending) {
      _publicCache.addRecord(record.first, record.second);
    }
  }
  // 更新线程LRU缓存
  std::lock_guard<std::mutex> lock(_mutex);
  for (auto& cache : _caches) {
    cache.second->update(_publicCache);
  }
}

// void CacheManager::init(const string& filename) {}
// LRUCache& CacheManager::getCache(size_t index) { return _caches[index]; }
