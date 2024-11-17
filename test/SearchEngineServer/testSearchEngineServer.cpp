#include <iostream>

#include "Configuration.h"
#include "SearchEngineServer.h"

int main(void) {
  Configuration* config = Configuration::getInstance();
  config->LoadConfig("../conf/config.json");
  json& server_conf = config->getConfigMap(SERVER);
  string ip = server_conf["HOST"];
  unsigned short port = server_conf["PORT"];
  SearchEngineServer server(ip, port);
  server.start();
  return 0;
}