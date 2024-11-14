#include <iostream>

#include "../include/SplitToolCppJieba.h"
using std::cout;

int main() {
  string str = R"(他来到了网易杭研大厦, I am a student
      IX.	The Adventure of the Engineer's Thumb
      the observer--excellent for drawing the veil from men's motives and actions.
      Grand Duke of Cassel-Felstein
      "No, no, there's life in him!"
      thisisasentence 苹果)";
  SplitToolCppJieba splitToolCppJieba;
  vector<string> words;
  splitToolCppJieba.cut(str, words);
  for (auto word : words) {
    cout << word << '/';
  }
  cout << '\n';
  return 0;
}