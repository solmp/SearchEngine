#include <iostream>

#include "../include/DirScanner.h"
int main() {
  DirScanner dir_scanner;
  dir_scanner.traversePath("../asset");
  for (const string& file : dir_scanner.getFiles()) {
    std::cout << file << '\n';
  }
  return 0;
}