#include "DictProducer.h"

DictProducer::DictProducer(SplitTool* tool) : _cuttor(tool) {}

void DictProducer::buildEnDict(const string& en_corpus_path) {
  // 获取所有英文语料路径
  DirScanner scanner;
  scanner.traversePath(en_corpus_path);
  // 遍历所有语料，统计词频
  for (const string& file_path : scanner.getFiles()) {
    ifstream ifs(file_path);
    if (!ifs) {
      throw std::runtime_error("ifstream open file error!");
    }
    string line;
    while (std::getline(ifs, line), !ifs.eof()) {
      // 语料清洗：非字母字符转换为空格，大写字母转换为小写字母
      for (auto& ch : line) {
        if (!isalpha(ch)) {
          ch = ' ';
        } else if (isupper(ch)) {
          ch = tolower(ch);
        }
      }
      // 词频统计
      istringstream iss(line);
      string word;
      while (iss >> word, !iss.eof()) {
        ++_freq_dict[word];
      }
    }
    ifs.close();
  }
}

void DictProducer::buildCnDict(const string& cn_corpus_path) {
  // 获取所有中文语料路径
  DirScanner scanner;
  scanner.traversePath(cn_corpus_path);
  // 遍历所有语料，cppjieba分词统计词频
  string line;
  for (const string& file_path : scanner.getFiles()) {
    string last_word = "";
    ifstream ifs(file_path);
    if (!ifs) {
      throw std::runtime_error("ifstream open file error!");
    }
    while (std::getline(ifs, line)) {
      vector<string> words;
      // 分词，将前一行最后一个词与本行第一个字符连接，以保证中文单词完整
      _cuttor->cut(last_word + line, words);
      // 词频统计
      size_t n = words.size();
      for (size_t i = 0; i < n - 1; ++i) {
        ++_freq_dict[words[i]];
      }
      if (n != 0) last_word = words[n - 1];
    }
    ++_freq_dict[last_word];
    ifs.close();
  }
}

void DictProducer::buildDict(Configuration* config,
                             const unordered_set<string>& stop_words) {
  json& assets = config->getConfigMap(ASSETS);
  string en_corpus_path = assets["EN_CORPUS_PATH"];
  string cn_corpus_path = assets["CN_CORPUS_PATH"];
  fprintf(stderr, "en_corpus_path: %s\n", en_corpus_path.c_str());
  fprintf(stderr, "cn_corpus_path: %s\n", cn_corpus_path.c_str());
  buildEnDict(en_corpus_path);  // 构建英文词典
  buildCnDict(cn_corpus_path);  // 构建中文词典
  fprintf(stderr, "en_dict size: %lu\n", _freq_dict.size());
  fprintf(stderr, "cn_dict size: %lu\n", _freq_dict.size());

  // 过滤停用词
  for (auto it = _freq_dict.begin(); it != _freq_dict.end();) {
    if (stop_words.find(it->first) != stop_words.end()) {
      it = _freq_dict.erase(it);
    } else {
      ++it;
    }
  }

  // 构建词典
  _dict.reserve(_freq_dict.size());
  _dict.assign(_freq_dict.begin(), _freq_dict.end());
}

void DictProducer::createIndex() {
  size_t size = _dict.size();
  for (size_t i = 0; i < size; ++i) {
    size_t len = _dict[i].first.size();
    for (size_t j = 0; j < len;) {
      // 计算字符所占字节数
      size_t width = nBytesCode(_dict[i].first[0]);
      // 截取字符，保存索引
      string word = _dict[i].first.substr(j, width);
      _index[word].insert(i);
      j += width;
    }
  }
}

void DictProducer::store(Configuration* config) {
  json& data_config = config->getConfigMap(DATA);
  // 存储词典
  ofstream ofs(data_config["DICT_PATH"]);
  if (!ofs) {
    throw std::runtime_error("ofstream open file error!");
  }
  for (auto item : _dict) {
    ofs << item.first << " " << item.second << '\n';
  }
  ofs.close();

  // 存储字符位置索引
  ofs.open(data_config["CHAR_INDEX_PATH"]);
  if (!ofs) {
    throw std::runtime_error("ofstream open file error!");
  }
  for (auto item : _index) {
    ofs << item.first;
    for (auto index : item.second) {
      ofs << " " << index;
    }
    ofs << '\n';
  }
  ofs.close();
}
