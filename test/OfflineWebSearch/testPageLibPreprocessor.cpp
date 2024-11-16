#include "PageLibPreprocessor.h"

int main() {
  Configuration* config = Configuration::getInstance();
  config->LoadConfig("../conf/config.json");
  json split_tool_conf = config->getConfigMap(SPLIT_TOOL);
  SplitTool* tool = new SplitToolCppJieba(split_tool_conf);
  PageLibPreprocessor plp(config, tool);
  plp.cutRedundantPage();
  plp.bulidInvertIndexMap();
  plp.storeOnDisk();
  return 0;
}