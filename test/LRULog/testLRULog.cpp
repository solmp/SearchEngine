#include "LRUCache.h"

int main() {
  LRUCache cache(5);
  cache.addRecord("1", {1, 2, 3});
  cache.addRecord("2", {{"a", "b"}, {"c", "d"}});

  fprintf(stdout, "cache.getRecord(\"1\") = %s\n",
          cache.getRecord("1").dump().c_str());
  fprintf(stdout, "cache.getRecord(\"2\") = %s\n",
          cache.getRecord("2").dump().c_str());
  return 0;
}