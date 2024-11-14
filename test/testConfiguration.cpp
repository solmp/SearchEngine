#include "../include/Configuration.h"

int main() {
  Configuration::getInstance()->LoadConfig("../conf/config.json");
  json split_tool_config = Configuration::getInstance()->getConfigMap(SPLIT_TOOL);
  std::cout << split_tool_config.dump(4) << std::endl;
  return 0;
}