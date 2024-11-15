#include <iostream>

#include "../include/DirScanner.h"
int main() {
  DirScanner dir_scanner;
  dir_scanner.traversePath("../asset");
  for (const string& file : dir_scanner.getFiles()) {
    fprintf(stdout, "file: %s\n", file.c_str());
  }
  return 0;
}