#include "RedisServer.h"

RedisServer* RedisServer::instance = nullptr;
const string RedisServer::redisDbName = "redisCache";

RedisServer::RedisServer()
    : _redis(Configuration::getInstance()->getConfigMap(REDIS)["URI"]) {}

RedisServer* RedisServer::getInstance() {
  if (instance == nullptr) {
    atexit(destroy);
    instance = new RedisServer();
  }
  return instance;
}

void RedisServer::destroy() {
  if (instance != nullptr) {
    delete instance;
    instance = nullptr;
  }
}

void RedisServer::addRecord(const string& key, const std::string& value) {
  _redis.hset(redisDbName, key, value);
}

bool RedisServer::query(const string& key, std::string& value) {
  std::optional<std::string> res = _redis.hget(redisDbName, key);
  if (res) {
    value = *res;
    return true;
  }
  return false;
}

bool RedisServer::checkConnect() {
  try {
    return (_redis.ping() == "PONG");
  } catch (const Error& e) {
    fprintf(stdout, "Redis start failed!\n");
    return false;
  }
}