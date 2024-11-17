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
  parser.doParse(request);  // 解析请求
  http_struct http_req = parser.getResult();
  http_req.print();

  parser.doParse(reponse);  // 解析响应
  http_struct http_resp = parser.getResult();
  http_resp.print();
  return 0;
}