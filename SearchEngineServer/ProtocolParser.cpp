#include "ProtocolParser.h"

llhttp_settings_t ProtocolParser::_settings = {
  on_message_begin : on_message_begin,        // 开始解析前
  on_url : on_url,                            // 解析url
  on_status : on_status,                      // 解析状态码
  on_header_field : on_header_field,          // 解析头部字段
  on_header_value : on_header_value,          // 解析头部值
  on_headers_complete : on_headers_complete,  // 头部解析完成
  on_body : on_body,                          // 解析body
  on_message_complete : on_message_complete   // 解析完成
};

ProtocolParser::http_struct ProtocolParser::_http = {};

void ProtocolParser::doParse(const string& data, size_t len) {
  // 初始化解析器， HTTP_BOTH表示自动选择解析请求还是响应
  llhttp_init(&_parser, HTTP_BOTH, &_settings);
  _http = {};
  enum llhttp_errno err = llhttp_execute(&_parser, data.c_str(), data.size());
  if (err != HPE_OK) {
    fprintf(stderr, "Parse error: %s %s\n", llhttp_errno_name(err),
            _parser.reason);
  }
}

void ProtocolParser::print() {
  fprintf(stderr, "parse_start_time: %ld\n", _http.parse_start_time);
  fprintf(stderr, "url: %s\n", _http.url.c_str());
  fprintf(stderr, "status: %s\n", _http.status.c_str());
  size_t size = _http.keys.size();
  for(size_t i = 0; i < size; i++) {
    fprintf(stderr, "[%s]: [%s]\n", _http.keys[i].c_str(), _http.values[i].c_str());
  }
  fprintf(stderr, "version: %d.%d\n", _http.major_version, _http.minor_version);
  fprintf(stderr, "upgrade: %d\n", _http.upgrade);
  fprintf(stderr, "keepalive: %d\n", _http.keepalive);
  fprintf(stderr, "header_end_time: %ld\n", _http.header_end_time);
  fprintf(stderr, "body: %s\n", _http.body.c_str());
  fprintf(stderr, "message_end_time: %ld\n\n", _http.message_end_time);
}

int ProtocolParser::on_message_begin(llhttp_t* parser) {
  _http.parse_start_time = time(nullptr);

  return 0;
}

int ProtocolParser::on_url(llhttp_t* parser, const char* at, size_t length) {
  strncpy(_http.url.data(), at, length);
  return 0;
}

int ProtocolParser::on_status(llhttp_t* parser, const char* at, size_t length) {
  strncpy(_http.status.data(), at, length);
  return 0;
}

int ProtocolParser::on_header_field(llhttp_t* parser, const char* at,
                                    size_t length) {
  char header_field[MAX_BUF_LEN] = {};
  strncpy(header_field, at, length);
  _http.keys.emplace_back(header_field);
  return 0;
}

int ProtocolParser::on_header_value(llhttp_t* parser, const char* at,
                                    size_t length) {
  char header_value[MAX_BUF_LEN] = {};
  strncpy(header_value, at, length);
  _http.values.emplace_back(header_value);
  return 0;
}

int ProtocolParser::on_headers_complete(llhttp_t* parser) {
  _http.major_version = parser->http_major;
  _http.minor_version = parser->http_minor;
  _http.upgrade = parser->upgrade;
  _http.keepalive = llhttp_should_keep_alive(parser);
  _http.header_end_time = time(nullptr);
  return 0;
}

int ProtocolParser::on_body(llhttp_t* parser, const char* at, size_t length) {
  strncpy(_http.body.data(), at, length);
  return 0;
}

int ProtocolParser::on_message_complete(llhttp_t* parser) {
  _http.message_end_time = time(nullptr);
  return 0;
}
