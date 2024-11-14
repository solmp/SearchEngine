#include <iostream>

#include "../include/DictProducer.h"

int main() {
  string corpus_path = "../asset/candidate";  // 语料文件/文件夹路径
  string dict_path = "../data/dict.dat";      // 词典路径
  string charIndex_path = "../data/dictIndex.dat";  // 字符位置索引
  string stop_words_path = "../asset/stop_words";   // 停用词路径

  unordered_set<string> stop_words;                          // 停用词集合
  DictProducer::LoadStopWords(stop_words_path, stop_words);  // 加载停用词

  DictProducer dictProducer(corpus_path, new SplitToolCppJieba);
  dictProducer.buildDict(stop_words);  // 创建词典
  dictProducer.createIndex();          // 创建字符位置索引
  dictProducer.store(dict_path, charIndex_path);
  return 0;
}