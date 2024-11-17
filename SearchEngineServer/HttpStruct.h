/**
 * @brief http 结构
 */
#ifndef _HTTP_STRUCT_H
#define _HTTP_STRUCT_H

#include <string>
#include <vector>

#include "llhttp.h"

using std::string;
using std::vector;

typedef struct http_struct {
  time_t parse_start_time;  // 解析开始时间
  llhttp_method method;     // 请求方法
  string url;               // url
  string status;            // 状态
  vector<string> keys;      // 键
  vector<string> values;    // 值
  int major_version;        // 主版本号
  int minor_version;        // 次版本号
  int upgrade;              // 升级
  int keepalive;            // 保持连接
  time_t header_end_time;   // 头部解析结束时间
  string body;              // 消息体
  time_t message_end_time;  // 消息解析结束时间

  void print() const {
    fprintf(stderr, "parse_start_time: %ld\n", parse_start_time);
    fprintf(stderr, "url: %s\n", url.c_str());
    fprintf(stderr, "status: %s\n", status.c_str());
    fprintf(stderr, "method: %s\n", llhttp_method_name(method));
    size_t size = keys.size();
    for (size_t i = 0; i < size; i++) {
      fprintf(stderr, "[%s]: [%s]\n", keys[i].c_str(), values[i].c_str());
    }
    fprintf(stderr, "version: %d.%d\n", major_version, minor_version);
    fprintf(stderr, "upgrade: %d\n", upgrade);
    fprintf(stderr, "keepalive: %d\n", keepalive);
    fprintf(stderr, "header_end_time: %ld\n", header_end_time);
    fprintf(stderr, "body: %s\n", body.c_str());
    fprintf(stderr, "message_end_time: %ld\n\n", message_end_time);
  }
} http_struct;

#endif  //_HTTP_STRUCT_H