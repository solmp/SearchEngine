#include "SearchEngineServer.h"

int main(void) {
  // 加载配置文件
  Configuration* config = Configuration::getInstance();
  config->LoadConfig("../conf/config.json");

  // 加载词典和位置索引
  Dictionary* dict = Dictionary::getInstance();
  dict->LoadDictionary(config);
  // 启动搜索引擎服务器
  json& server_conf = config->getConfigMap(SERVER);
  string ip = server_conf["HOST"];
  unsigned short port = server_conf["PORT"];
  SearchEngineServer server(ip, port);
  server.start();
  return 0;
}