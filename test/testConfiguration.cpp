#include "../include/Configuration.h"

int main() {
  Configuration::getInstance()->LoadConfig("../conf/config.json");
  json split_tool_config = Configuration::getInstance()->getConfigMap(SPLIT_TOOL);
  fprintf(stdout, "split_tool_config: %s\n", split_tool_config.dump(4).c_str());
  return 0;
}