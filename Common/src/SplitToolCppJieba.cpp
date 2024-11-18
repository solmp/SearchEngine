#include "SplitToolCppJieba.h"

SplitToolCppJieba* SplitToolCppJieba::pInstance = nullptr;

SplitToolCppJieba::SplitToolCppJieba(json& config)
    : _jieba(config["DICT_PATH"], config["HMM_PATH"], config["USER_DICT_PATH"],
             config["IDF_PATH"], config["STOP_WORD_PATH"]) {}

SplitToolCppJieba* SplitToolCppJieba::getInstance() {
  if (pInstance == nullptr) {
    atexit(destroy);
    json& config = Configuration::getInstance()->getConfigMap(SPLIT_TOOL);
    pInstance = new SplitToolCppJieba(config);
  }
  return pInstance;
}

void SplitToolCppJieba::destroy() {
  if (pInstance) {
    delete pInstance;
    pInstance = nullptr;
  }
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
