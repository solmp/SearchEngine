#include "SplitToolCppJieba.h"

const char* const DICT_PATH = "../3rdparty/include/cppjieba/dict/jieba.dict.utf8";
const char* const HMM_PATH = "../3rdparty/include/cppjieba/dict/hmm_model.utf8";
const char* const USER_DICT_PATH = "../3rdparty/include/cppjieba/dict/user.dict.utf8";
const char* const IDF_PATH = "../3rdparty/include/cppjieba/dict/idf.utf8";
const char* const STOP_WORD_PATH = "../3rdparty/include/cppjieba/dict/stop_words.utf8";

int main() {
  string str = R"(他来到了网易杭研大厦, I am a student
      IX.	The Adventure of the Engineer's Thumb
      the observer--excellent for drawing the veil from men's motives and actions.
      Grand Duke of Cassel-Felstein
      "No, no, there's life in him!"
      thisisasentence 苹果)";

  json config = {{"DICT_PATH", DICT_PATH},
                 {"HMM_PATH", HMM_PATH},
                 {"USER_DICT_PATH", USER_DICT_PATH},
                 {"IDF_PATH", IDF_PATH},
                 {"STOP_WORD_PATH", STOP_WORD_PATH}};

  SplitToolCppJieba splitToolCppJieba(config);
  vector<string> words;
  splitToolCppJieba.cut(str, words);
  for (auto word : words) {
    fprintf(stdout, "%s|", word.c_str());
  }
  fprintf(stdout, "\n");
  return 0;
}