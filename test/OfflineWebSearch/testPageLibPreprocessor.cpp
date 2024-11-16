#include "PageLibPreprocessor.h"

int main() {
  Configuration* config = Configuration::getInstance();
  config->LoadConfig("../conf/config.json");
  json split_tool_conf = config->getConfigMap(SPLIT_TOOL);
  SplitTool* tool = new SplitToolCppJieba(split_tool_conf);
  // 加载停用词
  unordered_set<string> stop_words;
  LoadStopWords(config->getConfigMap(ASSETS)["STOP_WORDS_PATH"], stop_words);
  PageLibPreprocessor plp(config, tool);
  plp.cutRedundantPage();
  plp.bulidInvertIndexMap(stop_words);
  plp.storeOnDisk();
  return 0;
}