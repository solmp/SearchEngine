#include "LRUCache.h"

json LRUCache::getRecord(string key) {
  unique_lock<mutex> ul(_mutex);
  auto it = _hashmap.find(key);
  if (it != _hashmap.end()) {
    _resultList.splice(_resultList.end(), _resultList, it->second);
    return _hashmap[key]->second;
  }
  return -1;
}

void LRUCache::addRecord(string key, json value) {
  unique_lock<mutex> ul(_mutex);
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

// void LRUCache::update(const LRUCache& cache) {
//   for (auto& it : cache._resultList) {
//     addRecord(it.first, it.second);
//   }
// }

// void LRUCache::load() {
//   string path =
//   Configuration::getInstance()->getConfigMap(DATA)["LRU_CACHE"]; ifstream
//   ifs(path); assert(ifs); json j; ifs >> j; for (auto& it : j.items()) {
//     addRecord(it.key(), it.value());
//   }
//   ifs.close();
// }

// void LRUCache::store() {
//   string path =
//   Configuration::getInstance()->getConfigMap(DATA)["LRU_CACHE"]; ofstream
//   ofs(path); assert(ofs); json j; for (auto& it : _resultList) {
//     j[it.first] = it.second;
//   }
//   ofs << j.dump(4);
//   ofs.close();
// }