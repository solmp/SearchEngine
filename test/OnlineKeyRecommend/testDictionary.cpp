#include "Dictionary.h"

int main() {
  Configuration* config = Configuration::getInstance();
  config->LoadConfig("../conf/config.json");
  Dictionary* dict = Dictionary::getInstance();
  dict->LoadDictionary(config);

  unordered_set<string> words;
  unordered_map<string, size_t> freq;
  dict->doQuery("谟", words, freq);
  size_t size = words.size();
  fprintf(stdout, "size = %lu\n", size);
  for (auto& word : words) {
    fprintf(stdout, "%s: %ld\n", word.c_str(), freq[word]);
  }
  return 0;
}