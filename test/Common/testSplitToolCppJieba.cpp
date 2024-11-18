#include "SplitToolCppJieba.h"

int main() {
  string str = R"(他来到了网易杭研大厦, I am a student
      IX.	The Adventure of the Engineer's Thumb
      the observer--excellent for drawing the veil from men's motives and actions.
      Grand Duke of Cassel-Felstein
      "No, no, there's life in him!"
      thisisasentence 苹果)";

  Configuration* config = Configuration::getInstance();
  config->LoadConfig("../conf/config.json");
  SplitToolCppJieba* splitToolCppJieba = SplitToolCppJieba::getInstance();
  vector<string> words;
  splitToolCppJieba->cut(str, words);
  for (auto word : words) {
    fprintf(stdout, "%s|", word.c_str());
  }
  fprintf(stdout, "\n");
  return 0;
}