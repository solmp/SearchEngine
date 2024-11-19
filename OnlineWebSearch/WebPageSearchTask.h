/**
 * @brief 网页搜索任务类
 */
#ifndef _WEBPAGE_SEARCH_TASK_H
#define _WEBPAGE_SEARCH_TASK_H

#include "HttpTask.h"
#include "WebPageSearcher.h"

class WebPageSearchTask : public HttpTask {
 public:
  /**
   * @brief 构造函数
   * @param conn 发起任务的连接
   * @param msg 待处理内容
   */
  WebPageSearchTask(TcpConnectionPtr conn, const string& msg)
      : HttpTask(std::move(conn), std::move(msg)) {}

  void process() override {
    // 获取缓存管理器
    CacheManager* cacheManager = CacheManager::getInstance();
    string res;
    if (cacheManager->queryRecord(_msg, res)) {
      fprintf(stdout, "[%ld]Cache hit\n", pthread_self());
      _conn->sendToLoop(
          std::bind(&TcpConnection::sendMsg, _conn, generateHttpResponse(res)));
      return;
    }
    // 缓存未命中，进行查询
    WebPageSearcher webPageSearcher(_msg, _conn);  // 创建网页搜索器
    webPageSearcher.doQuery();                     // 查询网页
    webPageSearcher.response();                    // 返回查询结果
  }
};

#endif  //_KEY_RECOMMAND_TASK_H