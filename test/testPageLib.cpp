#include "../include/PageLib.h"

int main() {
  Configuration* config = Configuration::getInstance();
  config->LoadConfig("../conf/config.json");

  fprintf(stdout, "%s\n", config->getConfigMap(ASSETS).dump(2).c_str());
  PageLib pageLib(config);
  pageLib.create();
  pageLib.store();
  return 0;
}