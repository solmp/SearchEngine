#include "../include/PageLib.h"

#include <iostream>

using std::cout;

int main() {
  Configuration* config = Configuration::getInstance();
  config->LoadConfig("../conf/config.json");

  cout << config->getConfigMap(ASSETS).dump(2) << std::endl;
  PageLib pageLib(config);
  pageLib.create();
  pageLib.store();
  return 0;
}