#include <iostream>

#include "../include/DictProducer.h"

int main() {
  string config_path = "../conf/config.json";     // 配置文件路径
  string corpus_path = "../asset/corpus";      // 语料文件/文件夹路径
  string dict_path = "../data/dict.dat";          // 词典路径
  string charIndex_path = "../data/dictIndex.dat";  // 字符位置索引
  string stop_words_path = "../asset/stop_words";   // 停用词路径

  unordered_set<string> stop_words;                          // 停用词集合
  DictProducer::LoadStopWords(stop_words_path, stop_words);  // 加载停用词

  Configuration::getInstance()->LoadConfig(config_path);
  json split_tool_config = Configuration::getInstance()->getConfigMap(SPLIT_TOOL);

  DictProducer dictProducer(corpus_path, new SplitToolCppJieba(split_tool_config));
  dictProducer.buildDict(stop_words);  // 创建词典
  dictProducer.createIndex();          // 创建字符位置索引
  dictProducer.store(dict_path, charIndex_path);  // 存储词典和字符位置索引
  return 0;
}