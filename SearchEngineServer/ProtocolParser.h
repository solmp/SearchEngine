/**
 * @brief http协议解析器
 */

#ifndef _PROTOCOLPARSER_H
#define _PROTOCOLPARSER_H

#include <stdio.h>

#include <cstring>
#include <ctime>
#include <functional>
#include <string>
#include <vector>

#include "NonCopyable.h"
#include "llhttp.h"

using std::bind;
using std::string;
using std::vector;
using namespace std::placeholders;

#define MAX_BUF_LEN 4096

class ProtocolParser : NonCopyable {
 public:
  /**
   * @brief 解析http请求或响应
   * @param data 报文数据
   * @param len 数据长度
   */
  void doParse(const string& data, size_t len);
  // 打印解析结果
  void print();

 private:
  // 解析开始回调函数
  static int on_message_begin(llhttp_t* parser);
  // 解析url回调函数
  static int on_url(llhttp_t* parser, const char* at, size_t length);
  // 解析状态码回调函数
  static int on_status(llhttp_t* parser, const char* at, size_t length);
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

  struct http_struct {
    time_t parse_start_time;      // 解析开始时间
    string url;                   // url
    string status;                // 状态
    vector<string> keys;          // 键
    vector<string> values;        // 值
    unsigned char major_version;  // 主版本号
    unsigned char minor_version;  // 次版本号
    unsigned char upgrade;        // 升级
    unsigned char keepalive;      // 保持连接
    time_t header_end_time;       // 头部解析结束时间
    string body;                  // 消息体
    time_t message_end_time;      // 消息解析结束时间
  };

 private:
  llhttp_t _parser;                    // 解析器
  static llhttp_settings_t _settings;  // 解析设置
  static http_struct _http;            // http 结构体
};

#endif  //_PROTOCOLPARSER_H