#include "DictProducer.h"

DictProducer::DictProducer(const string& corpus_path, SplitTool* tool)
    : _cuttor(tool) {
  DirScanner dir_scanner; 
  dir_scanner.traversePath(corpus_path);  // 获取所有语料文件路径   
  _files.swap(dir_scanner.getFiles());   
}

void DictProducer::buildDict(const unordered_set<string>& stop_words) {
  unordered_map<string, int> dict;
  // 分词并统计词频
  for (const string& filepath : _files) {
    ifstream ifs(filepath);
    if (!ifs) {
      throw std::runtime_error("ifstream open file error!");
    }
    string line;
    string last_word = "";
    while (std::getline(ifs, line)) {
      vector<string> words;
      // 如果上一行最后一个字符是字母，则与本行第一个字符连接，以保证中文单词完整
      if (!line.empty() && isalpha(line.front())) {
        last_word += " ";
      }
      // 将大写字母转换为小写字母
      for (auto& c : line) {
        if (isalpha(c)) {
          c = tolower(c);
        }
      }
      // 分词
      _cuttor->cut(last_word + line, words);
      // 词频统计
      size_t n = words.size();
      for (size_t i = 0; i < n - 1; ++i) {
        ++dict[words[i]];
      }
      if (n != 0) last_word = words[n - 1];
    }
    ++dict[last_word];
    ifs.close();
  }

  // 过滤停用词
  for (auto it = dict.begin(); it != dict.end();) {
    if (stop_words.find(it->first) != stop_words.end()) {
      it = dict.erase(it);
    } else {
      ++it;
    }
  }

  // 构建词典
  for (auto word : dict) {
    _dict.emplace_back(word);
  }
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

void DictProducer::store(const string& dict_path,
                         const string& charIndex_path) {
  // 存储词典
  ofstream ofs(dict_path);
  if (!ofs) {
    throw std::runtime_error("ofstream open file error!");
  }
  for (auto item : _dict) {
    ofs << item.first << " " << item.second << '\n';
  }
  ofs.close();

  // 存储字符位置索引
  ofs.open(charIndex_path);
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

void DictProducer::LoadStopWords(const string& stop_words_path,
                                 unordered_set<string>& stop_words) {
  DirScanner dir_scanner;
  dir_scanner.traversePath(stop_words_path);
  for (const string& stop_words_file : dir_scanner.getFiles()) {
    ifstream ifs(stop_words_file);
    if (!ifs) {
      throw std::runtime_error("ifstream open file error!");
    }
    string line;
    while (std::getline(ifs, line)) {
      // 去除末尾的回车换行
      if (!line.empty() && (line.back() == '\n' || line.back() == '\r')) {
        line.pop_back();
      }
      stop_words.insert(line);
    }
    ifs.close();
  }
}

size_t DictProducer::nBytesCode(const char ch) {
  if (ch & (1 << 7)) {
    int nBytes = 1;
    for (int i = 0; i < 6; ++i) {
      if (ch & (1 << (6 - i))) {
        ++nBytes;
      } else {
        break;
      }
    }
    return nBytes;
  }
  return 1;
}
