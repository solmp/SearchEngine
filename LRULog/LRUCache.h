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
   */
  bool getRecord(const string& key, string& value);
  /**
   * @brief 添加记录
   */
  void addRecord(const string& key, const string& value);
  /**
   * @brief 更新缓存
   * @param cache 新缓存
   */
  void update(const LRUCache& cache);
  /**
   * @brief 获取新缓存列表
   */
  list<std::pair<string, string>>& getPending();
  void load();
  void store();

 private:
  // 判满
  bool isFull() const { return _hashmap.size() >= _capacity; }

 private:
  size_t _capacity;
  list<std::pair<string, string>> _resultList;  // 记录缓存
  // 记录缓存的迭代器
  unordered_map<string, list<std::pair<string, string>>::iterator> _hashmap;
  // 新缓存列表
  list<std::pair<string, string>> _pendingUpdateList;
};

#endif  //_LRUCACHE_H