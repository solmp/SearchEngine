/**
 * @brief 关键词推荐在线模块
 */

#ifndef _KEYRECOMMANDER_H
#define _KEYRECOMMANDER_H

#include <sstream>

#include "Dictionary.h"
#include "ProtocolParser.h"
#include "TcpConnection.h"

using std::ostringstream;

#define KEY_RECOMMAND_NUM 5

class KeyRecommander {
 public:
  /**
   * @brief 构造函数
   * @param queryWord 用户输入内容
   * @param conn 客户端Tcp连接
   */
  KeyRecommander(const string& queryWord, TcpConnectionPtr conn)
      : _queryWord(queryWord), _conn(conn) {}
  /**
   * @brief 根据用户输入内容查找候选词
   */
  void doQuery();
  /**
   * @brief 响应客户端的请求(返回查询结果)
   * @note 将候选词结果包装为json格式，由主线程发送给客户端
   */
  void response();

  /**
   * @brief 获取结果，用于测试
   * @return priority_queue<CandidateResult>& 候选词结果优先队列
   */
  priority_queue<CandidateResult>& getResult() { return _candidateResultQue; }

 private:
  string _queryWord;                                    // 用户输入内容
  TcpConnectionPtr _conn;                               // 客户端Tcp连接
  priority_queue<CandidateResult> _candidateResultQue;  // 候选词结果优先队列
};

#endif  //_KEYRECOMMANDER_H