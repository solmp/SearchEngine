#include "../include/SplitToolCppJieba.h"

int main() {
  string str = R"(他来到了网易杭研大厦, I am a student
      IX.	The Adventure of the Engineer's Thumb
      the observer--excellent for drawing the veil from men's motives and actions.
      Grand Duke of Cassel-Felstein
      "No, no, there's life in him!"
      thisisasentence 苹果)";

  json config = {
      {"DICT_PATH", "../include/cppjieba/dict/jieba.dict.utf8"},
      {"HMM_PATH", "../include/cppjieba/dict/hmm_model.utf8"},
      {"USER_DICT_PATH", "../include/cppjieba/dict/user.dict.utf8"},
      {"IDF_PATH", "../include/cppjieba/dict/idf.utf8"},
      {"STOP_WORD_PATH", "../include/cppjieba/dict/stop_words.utf8"}};

  SplitToolCppJieba splitToolCppJieba(config);
  vector<string> words;
  splitToolCppJieba.cut(str, words);
  for (auto word : words) {
    fprintf(stdout, "%s|", word.c_str());
  }
  fprintf(stdout, "\n");
  return 0;
}