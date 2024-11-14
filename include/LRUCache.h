/**
 * Project SearchEngine
 */

#ifndef _LRUCACHE_H
#define _LRUCACHE_H

class LRUCache {
 public:
  /**
   * @param filename
   */
  void readFromFile(string& filename);

  /**
   * @param key
   * @param json
   */
  void addRecord(void key, void json);

  /**
   * @param const LRUCache&
   */
  void update(void const LRUCache&);

  /**
   * @param filename
   */
  void writeToFile(string& filename);

 private:
  void _resultList : list<pair<key, json>>;
  unordered_map<key, iterator> _hashmap;
  void _pendingUpdateList : list<pair<key, json>>;
};

#endif  //_LRUCACHE_H