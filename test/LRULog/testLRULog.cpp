#include "LRUCache.h"

int main() {
  Configuration::getInstance()->LoadConfig("../conf/config.json");
  LRUCache cache(5);
  cache.load();

  string res = "";
  cache.getRecord("1", res);
  fprintf(stdout, "cache.getRecord(\"1\") = %s\n", res.c_str());
  
  cache.addRecord("1", "{1, 2, 3}");
  cache.addRecord("2", R"({{"a", "b"}, {"c", "d"}})");
  cache.store();
  cache.getRecord("2", res);
  fprintf(stdout, "cache.getRecord(\"2\") = %s\n", res.c_str());
  return 0;
}