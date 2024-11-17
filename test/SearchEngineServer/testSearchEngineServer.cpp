#include <iostream>

#include "SearchEngineServer.h"

int main(void) {
  SearchEngineServer server("127.0.0.1", 8888);
  server.start();
  return 0;
}