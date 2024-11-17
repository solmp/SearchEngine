/**
 * @brief 候选词结果类
 */

#ifndef _CANDIDATERESULT_H
#define _CANDIDATERESULT_H

#include <string>

using std::string;

class CandidateResult {
 public:
  string _word;  // 候选词
  int _freq;     // 候选词频率
  int _dist;     // 候选词与用户输入内容的最短编辑距离

  /**
   * @brief 重载<运算符
   * @note 优先队列默认是大顶堆，因此需要重载<运算符为相反的比较方式
   * @param rhs 另一个候选词结果
   * @return true 当前对象小于rhs
   */
  friend bool operator<(const CandidateResult& lhs,
                        const CandidateResult& rhs) {
    if (lhs._dist == rhs._dist) {
      if (lhs._freq == rhs._freq) {
        return lhs._word > rhs._word;
      }
      return lhs._freq < rhs._freq;
    }
    return lhs._dist > rhs._dist;
  }
};

#endif  //_CANDIDATERESULT_H