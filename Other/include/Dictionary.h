/**
 * Project SearchEngine
 */

#ifndef _DICTIONARY_H
#define _DICTIONARY_H

class Dictionary {
 public:
  /**
   * @param key
   */
  vector<string> doQuery(const string& key);

 private:
  vector<pair<string, int>> _dict;
  map<set<int>> _index;

  void queryIndex();

  /**
   * @param candidate
   */
  int distance(string candidate);
};

#endif  //_DICTIONARY_H