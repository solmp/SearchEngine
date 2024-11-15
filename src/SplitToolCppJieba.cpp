#include "SplitToolCppJieba.h"

SplitToolCppJieba::SplitToolCppJieba(json config)
    : _jieba(config["DICT_PATH"], config["HMM_PATH"], config["USER_DICT_PATH"],
             config["IDF_PATH"], config["STOP_WORD_PATH"]) {}

void SplitToolCppJieba::cut(const string& str, vector<string>& words) {
  _jieba.Cut(str, words, true);
}

void LoadStopWords(const string& stop_words_path,
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

size_t nBytesCode(const char ch) {
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
