#include "CacheManager.h"

CacheManager* CacheManager::_instance = getInstance();

CacheManager* CacheManager::getInstance() {
  if (_instance == nullptr) {
    _instance = new CacheManager();
  }
  return _instance;
}

CacheManager::CacheManager() {}

void CacheManager::destroy() {
  if (_instance) {
    delete _instance;
    _instance = nullptr;
  }
}

void CacheManager::init(const string& filename) {}
LRUCache& CacheManager::getCache(size_t index) { return _caches[index]; }
void CacheManager::updateCache() {}