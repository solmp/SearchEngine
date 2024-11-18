/**
 * @brief LRU缓存类
 */

#ifndef _LRUCACHE_H
#define _LRUCACHE_H

#include <iostream>
#include <list>
#include <mutex>
#include <string>
#include <unordered_map>
#include <vector>

#include "Configuration.h"
#include "nlohmann/json.hpp"

using nlohmann::json;
using std::cin;
using std::cout;
using std::endl;
using std::list;
using std::mutex;
using std::ofstream;
using std::string;
using std::unique_lock;
using std::unordered_map;
using std::vector;

class LRUCache {
 public:
  LRUCache(int capacity = 5) : _capacity(capacity) {}
  /**
   * @brief 获取记录
   * @param key 键
   */
  json getRecord(string key);
  /**
   * @brief 添加记录
   * @param key 键
   * @param value 值
   */
  void addRecord(string key, json value);
  // void update(const LRUCache& cache);
  // void load();
  // void store();

 private:
  // 判满
  bool isFull() const { return _hashmap.size() >= _capacity; }

 private:
  size_t _capacity;
  list<std::pair<string, json>> _resultList;  // 记录缓存
  // 记录缓存的迭代器
  unordered_map<string, list<std::pair<string, json>>::iterator> _hashmap;
  mutex _mutex;
};

#endif  //_LRUCACHE_H