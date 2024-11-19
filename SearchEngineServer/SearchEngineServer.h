/**
 * @brief 搜索引擎服务器模块
 */
#ifndef _SEARCH_ENGINE_SERVER_H
#define _SEARCH_ENGINE_SERVER_H

#include "KeyRecommandTask.h"
#include "TcpServer.h"
#include "ThreadPool.h"
#include "TimerManager.h"
#include "WebPageSearchTask.h"

class SearchEngineServer {
 public:
  /**
   * @param ip 服务器ip地址
   * @param port 服务器端口号
   * @param threadNum 线程数量
   * @param queueSize 任务队列大小
   * @param initSec 定时器的起始时间
   * @param peridocSec 定时器的间隔时间
   */
  SearchEngineServer(const string& ip, unsigned short port, 
                     int threadNum, int queueSize, 
                     int initSec, int peridocSec);
  SearchEngineServer(const string& ip, unsigned short port);
  ~SearchEngineServer();
  // 启动搜索引擎服务器
  void start();
  // 停止搜索引擎服务器
  void stop();

 private:
  ThreadPool _pool;     // 线程池
  TcpServer _server;    // Tcp服务器
  TimerManager _timer;  // 定时器

  /**
   * @brief 处理新客户端连接
   * @param conn 连接
   */
  void OnNewConnection(const TcpConnectionPtr& conn);
  /**
   * @brief 处理客户端消息
   * @param conn 连接
   */
  void OnMessage(const TcpConnectionPtr& conn);
  /**
   * @brief 客户端断开连接
   * @param conn 连接
   */
  void OnClose(const TcpConnectionPtr& conn);
};

#endif  //_SEARCH_ENGINE_SERVER_H