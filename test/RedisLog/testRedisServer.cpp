#include "RedisServer.h"

int main() {
  Configuration::getInstance()->LoadConfig("../conf/config.json");
  auto redis = RedisServer::getInstance();

  redis->addRecord("key1", "val");
  std::string val;
  if (redis->query("key1", val)) {
    fprintf(stdout, "key1: %s\n", val.c_str());
  } else {
    fprintf(stdout, "key1 not found\n");
  }

  if (redis->query("key2", val)) {
    fprintf(stdout, "key2: %s\n", val.c_str());
  } else {
    fprintf(stdout, "key2 not found\n");
  }
  return 0;
}