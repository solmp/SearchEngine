#include <iostream>

#include "../include/SplitToolCppJieba.h"
using std::cout;

int main() {
  string str = "他来到了网易杭研大厦, I am a student";
  SplitToolCppJieba splitToolCppJieba;
  vector<string> words;
  splitToolCppJieba.cut(str, words);
  for (auto word : words) {
    cout << word << '/';
  }
  cout << '\n';
  return 0;
}