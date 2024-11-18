#include "CacheManager.h"

CacheManager* CacheManager::_instance = getInstance();

CacheManager* CacheManager::getInstance() {
  if (_instance == nullptr) {
    atexit(destroy);
    _instance = new CacheManager();
  }
  return _instance;
}

CacheManager::CacheManager() {
  _caches.emplace_back(5);  // 此版本中只有一个公共LRU缓存
}

void CacheManager::destroy() {
  if (_instance) {
    delete _instance;
    _instance = nullptr;
  }
}

bool CacheManager::queryPublicCache(const string& key, string& value) {
  // 1.查询Redis缓存
  RedisServer* redisServer = RedisServer::getInstance();
  if (redisServer->query(key, value)) {
    return true;
  }
  // 2.查询LRU缓存
  unique_lock<mutex> lock(_mutex);
  if (_caches[0].getRecord(key, value)) {
    return true;
  }
  return false;
}

void CacheManager::addPublicCache(const string& key, const string& value) {
  // 1.添加Redis缓存
  RedisServer::getInstance()->addRecord(key, value);
  // 2.添加LRU缓存
  unique_lock<mutex> lock(_mutex);
  _caches[0].addRecord(key, value);
}

// void CacheManager::init(const string& filename) {}
// LRUCache& CacheManager::getCache(size_t index) { return _caches[index]; }
// void CacheManager::updateCache() {}