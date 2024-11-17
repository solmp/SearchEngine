#include "KeyRecommander.h"

int main() {
  // 初始化配置信息
  Configuration* config = Configuration::getInstance();
  config->LoadConfig("../conf/config.json");
  // 初始化词典
  Dictionary* dict = Dictionary::getInstance();
  dict->LoadDictionary(config);
  KeyRecommander keyRecommander("hello", nullptr);
  keyRecommander.doQuery();

  priority_queue<CandidateResult>& result = keyRecommander.getResult();
  size_t size =
      result.size() < KEY_RECOMMAND_NUM ? result.size() : KEY_RECOMMAND_NUM;
  fprintf(stderr, "size: %lu\n", size);
  for (size_t i = 0; i < size; ++i) {
    CandidateResult candidate = result.top();
    result.pop();
    fprintf(stderr, "word: %s\n", candidate._word.c_str());
  }
  return 0;
}