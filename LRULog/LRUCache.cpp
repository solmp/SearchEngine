#include "LRUCache.h"

bool LRUCache::getRecord(const string& key, string& value) {
  auto it = _hashmap.find(key);
  if (it != _hashmap.end()) {
    _resultList.splice(_resultList.end(), _resultList, it->second);
    value = _hashmap[key]->second;
    return true;
  }
  return false;
}

void LRUCache::addRecord(const string& key, const string& value) {
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

void LRUCache::load() {
  try {
    string path = Configuration::getInstance()->getConfigMap(DATA)["LRU_CACHE"];
    ifstream ifs(path);
    assert(ifs);
    json j;
    ifs >> j;
    for (auto& it : j.items()) {
      addRecord(it.key(), it.value());
    }
    ifs.close();
  } catch (nlohmann::json::parse_error& e) {
    fprintf(stderr, "json parse error: %s\n", e.what());
  }
}

void LRUCache::store() {
  string path = Configuration::getInstance()->getConfigMap(DATA)["LRU_CACHE"];
  ofstream ofs(path);
  assert(ofs);
  json j;
  for (auto& it : _resultList) {
    j[it.first] = it.second;
  }
  ofs << j.dump(4);
  ofs.close();
}