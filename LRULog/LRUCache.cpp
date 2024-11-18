#include "LRUCache.h"

json LRUCache::getRecord(string key) {
  auto it = _hashmap.find(key);
  if (it != _hashmap.end()) {
    _resultList.splice(_resultList.end(), _resultList, it->second);
    return _hashmap[key]->second;
  }
  return -1;
}

void LRUCache::addRecord(string key, json value) {
  auto it = _hashmap.find(key);
  if (it != _hashmap.end()) {
    _resultList.splice(_resultList.end(), _resultList, it->second);
    _resultList.back().second = value;
  } else if (isFull()) {
    _hashmap.erase(_resultList.front().first);
    _resultList.pop_front();
    _resultList.emplace_back(key, value);
  } else {
    _resultList.emplace_back(key, value);
  }
  _hashmap[key] = --_resultList.end();
}

void LRUCache::update(const LRUCache& cache) {}
void LRUCache::load(string& filename) {}
void LRUCache::store(string& filename) {}