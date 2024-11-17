/**
 * @brief http协议解析器
 */

#ifndef _PROTOCOLPARSER_H
#define _PROTOCOLPARSER_H

#include <stdio.h>

#include <cstring>
#include <ctime>
#include <functional>

#include "HttpStruct.h"
#include "NonCopyable.h"

using std::bind;

using namespace std::placeholders;

#define MAX_BUF_LEN 4096

class ProtocolParser : NonCopyable {
 public:
  /**
   * @brief 解析http请求或响应
   * @param data 报文数据
   * @param len 数据长度
   */
  void doParse(const string& data);
  // 获取解析结果
  http_struct&& getResult() { return std::move(_http); }

 private:
  // 解析开始回调函数
  static int on_message_begin(llhttp_t* parser);
  // 解析url回调函数
  static int on_url(llhttp_t* parser, const char* at, size_t length);
  // 解析状态码回调函数
  static int on_status(llhttp_t* parser, const char* at, size_t length);
  // 解析请求方法回调函数
  static int on_method(llhttp_t* parser, const char* at, size_t length);
  // 解析 header key 回调函数
  static int on_header_field(llhttp_t* parser, const char* at, size_t length);
  // 解析  header value 回调函数
  static int on_header_value(llhttp_t* parser, const char* at, size_t length);
  // 头部解析完成回调函数
  static int on_headers_complete(llhttp_t* parser);
  // 解析body回调函数
  static int on_body(llhttp_t* parser, const char* at, size_t length);
  // 解析完成回调函数
  static int on_message_complete(llhttp_t* parser);

 private:
  llhttp_t _parser;                    // 解析器
  static llhttp_settings_t _settings;  // 解析设置
  static http_struct _http;            // http 结构体
};

/**
 * @brief 生成http响应
 * @param body 响应体
 * @return 响应报文
 */
string generateHttpResponse(const string& body);

#endif  //_PROTOCOLPARSER_H