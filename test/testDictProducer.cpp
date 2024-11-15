#include "../include/DictProducer.h"

int main() {
  Configuration* config = Configuration::getInstance();
  config->LoadConfig("../conf/config.json");

  SplitTool* tool = new SplitToolCppJieba(config->getConfigMap(SPLIT_TOOL));
  unordered_set<string> stop_words;  // 停用词集合

  // 加载停用词
  LoadStopWords(config->getConfigMap(ASSETS)["STOP_WORDS_PATH"], stop_words);
  DictProducer dictProducer(tool);
  dictProducer.buildDict(config, stop_words);  // 创建词典
  dictProducer.createIndex();                  // 创建字符位置索引
  dictProducer.store(config);  // 存储词典和字符位置索引
  return 0;
}