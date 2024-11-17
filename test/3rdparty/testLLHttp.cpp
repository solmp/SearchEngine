#include <stdio.h>
#include <string.h>

#include "llhttp.h"

#define MAX_LEN 2048

int on_message_begin(llhttp_t* parser) {
  printf("parse start\n");
  return 0;
}

int on_url(llhttp_t* parser, const char* at, size_t length) {
  char url[MAX_LEN];
  strncpy(url, at, length);
  url[length] = '\0';
  printf("on_url: %s\n", url);
  return 0;
}

int on_status(llhttp_t* parser, const char* at, size_t length) {
  char status[MAX_LEN];
  strncpy(status, at, length);
  status[length] = '\0';
  printf("on_status: %s\n", status);
  return 0;
}

int on_header_field(llhttp_t* parser, const char* at, size_t length) {
  char header_field[MAX_LEN];
  strncpy(header_field, at, length);
  header_field[length] = '\0';
  printf("head field: %s\n", header_field);
  return 0;
}

int on_header_value(llhttp_t* parser, const char* at, size_t length) {
  char header_value[MAX_LEN];
  strncpy(header_value, at, length);
  header_value[length] = '\0';
  printf("head value: %s\n", header_value);
  return 0;
}

int on_headers_complete(llhttp_t* parser) {
  printf("on_headers_complete, major: %d, major: %d, keep-alive: %d, upgrade: %d\n",
          parser->http_major, parser->http_minor, llhttp_should_keep_alive(parser),
          parser->upgrade);
  return 0;
}

int on_body(llhttp_t* parser, const char* at, size_t length) {
  char body[MAX_LEN];
  strncpy(body, at, length);
  body[length] = '\0';
  printf("on_body: %s\n", body);
  return 0;
}

int on_message_complete(llhttp_t* parser) {
  printf("on_message_complete\n");
  return 0;
}

int main() {
  llhttp_t parser;                  // 创建解析器
  llhttp_settings_t settings;       // 创建设置
  llhttp_settings_init(&settings);  // 初始化设置
  llhttp_init(&parser, HTTP_BOTH, &settings);  // 初始化解析器， HTTP_BOTH表示自动选择解析请求还是响应

  // 设置回调函数
  settings.on_message_begin = on_message_begin;        // 开始解析前
  settings.on_url = on_url;                            // 解析url
  settings.on_status = on_status;                      // 解析状态码
  settings.on_header_field = on_header_field;          // 解析头部字段
  settings.on_header_value = on_header_value;          // 解析头部值
  settings.on_headers_complete = on_headers_complete;  // 头部解析完成
  settings.on_body = on_body;                          // 解析body
  settings.on_message_complete = on_message_complete;  // 解析完成

  // 解析响应
  const char* reponse =
      "HTTP/1.1 200 OK\r\n"
      "Server: nginx\r\n"
      "content-length: 11\r\n"
      "\r\n"
      "hello:world\r\n"
      "\r\n";
  int reponse_len = strlen(reponse);
  enum llhttp_errno err = llhttp_execute(&parser, reponse, reponse_len);
  if (err != HPE_OK) {
    fprintf(stderr, "Parse error: %s %s\n", llhttp_errno_name(err), parser.reason);
  }

  // 解析请求
  const char* request =
      "POST /index.html HTTP/1.1\r\n"
      "connection:close\r\n"
      "content-length: 1\r\n"
      "\r\n"
      "1\r\n"
      "\r\n";
  int request_len = strlen(request);
  err = llhttp_execute(&parser, request, request_len);
  if (err != HPE_OK) {
    fprintf(stderr, "Parse error: %s %s\n", llhttp_errno_name(err), parser.reason);
  }
  return 0;
}