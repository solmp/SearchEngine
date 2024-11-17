#include "ProtocolParser.h"

int main() {
  const char* request =
      "POST /index.html HTTP/1.1\r\n"
      "connection:close\r\n"
      "content-length: 1\r\n"
      "\r\n"
      "1\r\n"
      "\r\n";
  const char* reponse =
      "HTTP/1.1 200 OK\r\n"
      "Server: nginx\r\n"
      "content-length: 11\r\n"
      "\r\n"
      "hello:world\r\n"
      "\r\n";

  ProtocolParser parser;
  parser.doParse(request, strlen(request)); // 解析请求
  parser.print();
  parser.doParse(reponse, strlen(reponse)); // 解析响应
  parser.print();
  return 0;
}