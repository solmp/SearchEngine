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
  // 加入待更新列表
  if (_pendingUpdateList.size() >= _capacity) {
    _pendingUpdateList.pop_front();
  }
  _pendingUpdateList.push_back(*_hashmap[key]);
}

list<std::pair<string, string>>& LRUCache::getPending() {
  return _pendingUpdateList;
}

void LRUCache::update(const LRUCache& cache) {
  _resultList = cache._resultList;
  _hashmap.clear();
  for (auto it = _resultList.begin(); it != _resultList.end(); ++it) {
    _hashmap[it->first] = it;
  }
}

void LRUCache::load() {
  try {
    string path = Configuration::getInstance()->getConfigMap(DATA)["LRU_CACHE"];
    ifstream in(path, std::ios::in);
    if (!in) {
      fprintf(stderr, "open file %s failed\n", path.c_str());
      return;
    }
    std::istreambuf_iterator<char> beg(in), end;
    string strdata(beg, end);
    in.close();
    json j = json::parse(strdata);
    for (auto& it : j.items()) {
      addRecord(it.key(), it.value());
    }
  } catch (nlohmann::json::parse_error& e) {
    fprintf(stderr, "json parse error: %s\n", e.what());
  } catch (std::exception& e) {
    fprintf(stderr, "exception: %s\n", e.what());
  }
}

void LRUCache::store() {
  string path = Configuration::getInstance()->getConfigMap(DATA)["LRU_CACHE"];
  ofstream ofs(path);
  assert(ofs);
  json j = json::object();
  for (auto& it : _resultList) {
    j[it.first] = it.second;
  }
  ofs << j.dump(4);
  ofs.close();
}