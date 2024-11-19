#include "ProtocolParser.h"

llhttp_settings_t ProtocolParser::_settings = {
  on_message_begin : on_message_begin,        // 开始解析前
  on_url : on_url,                            // 解析url
  on_status : on_status,                      // 解析状态码
  on_method : on_method,                      // 解析请求方法
  on_header_field : on_header_field,          // 解析头部字段
  on_header_value : on_header_value,          // 解析头部值
  on_headers_complete : on_headers_complete,  // 头部解析完成
  on_body : on_body,                          // 解析body
  on_message_complete : on_message_complete   // 解析完成
};

http_struct ProtocolParser::_http = {};

void ProtocolParser::doParse(const string& data) {
  // 初始化解析器， HTTP_BOTH表示自动选择解析请求还是响应
  llhttp_init(&_parser, HTTP_BOTH, &_settings);
  _http = {};
  enum llhttp_errno err = llhttp_execute(&_parser, data.c_str(), data.size());
  if (err != HPE_OK) {
    fprintf(stderr, "Parse error: %s %s\n", llhttp_errno_name(err),
            _parser.reason);
  }
}
int ProtocolParser::on_message_begin(llhttp_t* parser) {
  _http.parse_start_time = time(nullptr);
  return 0;
}

int ProtocolParser::on_url(llhttp_t* parser, const char* at, size_t length) {
  _http.url = string(at, length);
  return 0;
}

int ProtocolParser::on_status(llhttp_t* parser, const char* at, size_t length) {
  _http.status = string(at, length);
  return 0;
}

int ProtocolParser::on_method(llhttp_t* parser, const char* at, size_t length) {
  _http.method = llhttp_method(parser->method);
  return 0;
}

int ProtocolParser::on_header_field(llhttp_t* parser, const char* at,
                                    size_t length) {
  _http.keys.emplace_back(string(at, length));
  return 0;
}

int ProtocolParser::on_header_value(llhttp_t* parser, const char* at,
                                    size_t length) {
  _http.values.emplace_back(string(at, length));
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
  _http.body = string(at, length);
  return 0;
}

int ProtocolParser::on_message_complete(llhttp_t* parser) {
  _http.message_end_time = time(nullptr);
  return 0;
}

string generateHttpResponse(const string& body) {
  ostringstream oss;
  time_t now = time(nullptr);
  struct tm* gmtNow = gmtime(&now);
  char buffer[80] = {};
  strftime(buffer, sizeof(buffer), "%a, %d %b %Y %H:%M:%S GMT", gmtNow);
  oss << "HTTP/1.1 200 OK\r\n"
      << "Content-Type: application/json\r\n"
      << "Content-Length: " << body.size() << "\r\n"
      << "Server: MyServer\r\n"
      << "Date: " << buffer << "\r\n"
      << "\r\n"
      << body << "\r\n";
  return oss.str();
}
