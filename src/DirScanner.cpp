#include "DirScanner.h"

vector<string>& DirScanner::getFiles() { return _files; }

void DirScanner::traversePath(const string& path) {
  _files.clear();
  if (std::filesystem::is_directory(path)) {
    for (const auto& entry :
         std::filesystem::recursive_directory_iterator(path)) {
      if (entry.is_regular_file()) {
        _files.push_back(entry.path().string());
      }
    }
  } else if (std::filesystem::is_regular_file(path)) {
    _files.push_back(path);
  }
}