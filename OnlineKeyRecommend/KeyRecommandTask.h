/**
 * @brief 关键词推荐任务类
 */
#ifndef _KEY_RECOMMAND_TASK_H
#define _KEY_RECOMMAND_TASK_H

#include "HttpTask.h"
#include "KeyRecommander.h"

class KeyRecommandTask : public HttpTask {
 public:
  /**
   * @brief 构造函数
   * @param conn 发起任务的连接
   * @param msg 待处理内容
   */
  KeyRecommandTask(TcpConnectionPtr conn, const string& msg)
      : HttpTask(std::move(conn), std::move(msg)) {}
  void process() override {
    {
      KeyRecommander keyRecommander(_msg, _conn);  // 创建关键词推荐器
      keyRecommander.doQuery();                    // 查询候选词
      keyRecommander.response();                   // 返回查询结果
    }
  }
};

#endif  //_KEY_RECOMMAND_TASK_H