#include "Dictionary.h"

Dictionary* Dictionary::_pInstance = getInstance();

Dictionary* Dictionary::getInstance() {
  if (_pInstance == nullptr) {
    atexit(destroy);
    _pInstance = new Dictionary();
  }
  return _pInstance;
}

void Dictionary::destroy() {
  if (_pInstance != nullptr) {
    delete _pInstance;
    _pInstance = nullptr;
  }
}

void Dictionary::LoadDictionary(Configuration* config) {
  // 加载词典
  string dict_path = config->getConfigMap(DATA)["DICT_PATH"];
  ifstream dict_ifs(dict_path);
  assert(dict_ifs);
  string line;
  while (getline(dict_ifs, line)) {
    istringstream iss(line);
    string word;
    int freq;
    iss >> word >> freq;
    _dict.emplace_back(make_pair(word, freq));
  }
  dict_ifs.close();
  // 加载位置索引
  string index_path = config->getConfigMap(DATA)["CHAR_INDEX_PATH"];
  ifstream index_ifs(index_path);
  assert(index_ifs);
  while (getline(index_ifs, line)) {
    istringstream iss(line);
    string ch;
    int pos;
    iss >> ch;
    unordered_set<int> pos_set;
    while (iss >> pos) {
      pos_set.insert(pos);
    }
    _index.insert(make_pair(ch, move(pos_set)));
  }
  index_ifs.close();
}

void Dictionary::doQuery(const string& ch, unordered_set<string>& words,
                         unordered_map<string, size_t>& freq) {
  vector<pair<string, size_t>> res;
  // 查询索引，得到字符对应单词集合
  if (_index.find(ch) != _index.end()) {
    for (auto pos : _index[ch]) {
      res.emplace_back(_dict[pos]);
      auto res = words.insert(_dict[pos].first);  // 插入单词集合
      if (res.second) {
        // 如果插入成功，说明该单词是新的，记录词频
        freq[_dict[pos].first] = _dict[pos].second;
      }
    }
  }
}
