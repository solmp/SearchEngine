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
  // 接收http请求
  string msg = move(conn->readMsg());
  // 创建请求对应的任务
  KeyRecommandTask task(conn, msg);
  _pool.addTask(std::bind(&KeyRecommandTask::process, task));
}

void SearchEngineServer::OnClose(const TcpConnectionPtr& conn) {
  cout << "OnClose" << endl;
}