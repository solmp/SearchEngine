/**
 * @brief LRU缓存类
 */

#ifndef _LRUCACHE_H
#define _LRUCACHE_H

#include <iostream>
#include <list>
#include <string>
#include <unordered_map>
#include <vector>

#include "nlohmann/json.hpp"

using nlohmann::json;
using std::cin;
using std::cout;
using std::endl;
using std::list;
using std::string;
using std::unordered_map;
using std::vector;

class LRUCache {
 public:
  LRUCache(int capacity = 5) : _capacity(capacity) {}
  json getRecord(string key);
  void addRecord(string key, json value);
  void update(const LRUCache& cache);
  void load(string& filename);
  void store(string& filename);

 private:
  bool isFull() const { return _hashmap.size() >= _capacity; }

 private:
  size_t _capacity;
  list<std::pair<string, json>> _resultList;
  unordered_map<string, list<std::pair<string, json>>::iterator> _hashmap;
};

#endif  //_LRUCACHE_H