#include "SplitToolCppJieba.h"

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
