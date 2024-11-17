#include "KeyRecommander.h"

void KeyRecommander::doQuery() {
  Dictionary* dict = Dictionary::getInstance();  // 获取词典单例
  // 遍历字符，查询词典中对应的单词集合的并集
  size_t len = _queryWord.size();
  unordered_set<string> words;
  unordered_map<string, size_t> freq;
  for (size_t i = 0; i < len;) {
    // 获取字符
    size_t nBytes = nBytesCode(_queryWord[i]);
    string ch = _queryWord.substr(i, nBytes);
    i += nBytes;
    // 查询词典
    dict->doQuery(ch, words, freq);
  }

  // 计算最短编辑距离并插入优先队列
  CandidateResult candidate;
  for (auto& word : words) {
    candidate._word = word;
    candidate._freq = freq[word];
    candidate._dist = editDistance(_queryWord, word);
    _candidateResultQue.emplace(candidate);
  }
}

void KeyRecommander::response() {
  // 将候选词结果包装为json格式返回给客户端
  size_t size = _candidateResultQue.size() < KEY_RECOMMAND_NUM
                    ? _candidateResultQue.size()
                    : KEY_RECOMMAND_NUM;
  json json_body = {
      {"size", size},
      {"result", json::array()},
  };
  for (size_t i = 0; i < size; ++i) {
    CandidateResult candidate = _candidateResultQue.top();
    _candidateResultQue.pop();
    json_body["result"].push_back(candidate._word);
  }
  string response = generateHttpResponse(json_body.dump());
  _conn->sendToLoop(std::bind(&TcpConnection::sendMsg, _conn, response));
}
