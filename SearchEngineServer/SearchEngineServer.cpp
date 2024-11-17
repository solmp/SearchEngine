#include "SearchEngineServer.h"

SearchEngineServer::SearchEngineServer(const string& ip, unsigned short port)
    : _server(ip, port) {}

SearchEngineServer::SearchEngineServer(const string& ip, unsigned short port,
                                       int threadNum, int queueSize)
    : _pool(threadNum, queueSize), _server(ip, port) {}

SearchEngineServer::~SearchEngineServer() { stop(); }

void SearchEngineServer::start() {
  _pool.start();
  _server.setAllCallback(
      std::bind(&SearchEngineServer::OnNewConnection, this,
                std::placeholders::_1),
      std::bind(&SearchEngineServer::OnMessage, this, std::placeholders::_1),
      std::bind(&SearchEngineServer::OnClose, this, std::placeholders::_1));
  _server.start();
}

void SearchEngineServer::stop() {
  _pool.stop();
  _server.stop();
}

void SearchEngineServer::OnNewConnection(const TcpConnectionPtr& conn) {
  cout << "OnNewConnection" << endl;
}

void SearchEngineServer::OnMessage(const TcpConnectionPtr& conn) {
  // 接收并解析http请求
  string msg = move(conn->readMsg());
  ProtocolParser parser;                        // 创建解析器
  parser.doParse(msg);                          // 解析http请求
  http_struct http_req = parser.getResult();    // 获取解析结果
  http_req.print();                             // 打印http请求
  json json_body = json::parse(http_req.body);  // 解析json格式的请求体
  TaskType type = json_body["type"];            // 获取任务类型
  string data = json_body["data"];              // 获取用户输入内容
  // 创建请求对应的任务
  if (type == KEY_RECOMMAND) {
    KeyRecommandTask task(conn, data);
    _pool.addTask(std::bind(&KeyRecommandTask::process, task));
  } else if (type == WEB_PAGE_SEARCH) {
    WebPageSearchTask task(conn, data);
    _pool.addTask(std::bind(&WebPageSearchTask::process, task));
  }
}

void SearchEngineServer::OnClose(const TcpConnectionPtr& conn) {
  cout << "OnClose" << endl;
}