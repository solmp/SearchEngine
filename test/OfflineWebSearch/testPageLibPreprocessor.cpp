#include "PageLibPreprocessor.h"

int main() {
  Configuration* config = Configuration::getInstance();
  config->LoadConfig("../conf/config.json");
  SplitTool* tool = SplitToolCppJieba::getInstance();
  // 加载停用词
  unordered_set<string> stop_words;
  LoadStopWords(config->getConfigMap(ASSETS)["STOP_WORDS_PATH"], stop_words);
  PageLibPreprocessor plp(config, tool);
  plp.cutRedundantPage();
  plp.bulidInvertIndexMap(stop_words);
  plp.storeOnDisk();
  return 0;
}