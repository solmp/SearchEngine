#include "WebPageQuery.h"

WebPageQuery* WebPageQuery::_pInstance = nullptr;

WebPageQuery::WebPageQuery() {
  // 获取分词工具和所需数据（去重网页偏移库、倒排索引、停用词）
  _wordCutTool = SplitToolCppJieba::getInstance();
  Configuration* config = Configuration::getInstance();
  // 加载去重网页偏移库
  loadOffsetLib(config->getConfigMap(DATA)["UNIQUE_PAGE_OFFSET_PATH"]);
  // 加载倒排索引
  loadInvertIndexLib(config->getConfigMap(DATA)["INVERT_INDEX_PATH"]);
  // 加载停用词
  LoadStopWords(config->getConfigMap(SPLIT_TOOL)["STOP_WORD_PATH"],
                _stop_words);
}

WebPageQuery* WebPageQuery::getInstance() {
  if (_pInstance == nullptr) {
    atexit(destroy);
    _pInstance = new WebPageQuery();
  }
  return _pInstance;
}

void WebPageQuery::destroy() {
  if (_pInstance) {
    delete _pInstance;
  }
}

void WebPageQuery::loadOffsetLib(const string& offsetLibPath) {
  ifstream ifs(offsetLibPath);
  assert(ifs);
  string line;
  while (std::getline(ifs, line)) {
    istringstream iss(line);
    size_t doc_id, offset, size;
    iss >> doc_id >> offset >> size;
    _offsetLib[doc_id] = make_pair(offset, size);
  }
  ifs.close();
}

void WebPageQuery::loadInvertIndexLib(const string& invertIndexLibPath) {
  ifstream ifs(invertIndexLibPath);
  assert(ifs);
  string line;
  while (std::getline(ifs, line)) {
    istringstream iss(line);
    string word;
    iss >> word;
    size_t doc_id;
    double weight;
    while (iss >> doc_id >> weight) {
      _invertIndexLib[word].push_back(make_pair(doc_id, weight));
    }
  }
  ifs.close();
}

void WebPageQuery::doQuery(const string& key, vector<size_t>& _webPages) {
  // 句子分词
  vector<string> words;
  _wordCutTool->cut(key, words);
  vector<string> tmp;
  for (auto& word : words) {
    // 过滤停用词
    if (_stop_words.find(word) == _stop_words.end()) {
      tmp.emplace_back(word);
      continue;
    }
  }
  words.swap(tmp);
  // 统计词频
  unordered_map<string, size_t> wordFreq;
  for (auto& word : words) {
    ++wordFreq[word];
  }
  // 查询字符对应文章的交集
  unordered_map<size_t, double> intersection(_invertIndexLib[words[0]].begin(),
                                             _invertIndexLib[words[0]].end());
  for (size_t i = 1; i < words.size(); ++i) {
    unordered_map<size_t, double> tmp(_invertIndexLib[words[i]].begin(),
                                      _invertIndexLib[words[i]].end());
    auto it = _invertIndexLib[words[i]].begin();
    while (it != _invertIndexLib[words[i]].end()) {
      if (intersection.find(it->first) == intersection.end()) {
        tmp.erase(it->first);
      }
      ++it;
    }
    intersection.swap(tmp);
  }
  fprintf(stdout, "intersection size: %ld\n", intersection.size());

  // 把句子当作文章计算权重
  unordered_map<string, double> doc_w;  // 用于保存每个单词的权重
  size_t N = _offsetLib.size() + 1;     // N: 网页库文档总数
  for (auto& item : wordFreq) {
    string word = item.first;
    size_t TF = item.second;  // TF：该词在文档中出现的次数
    size_t DF = 1;
    auto it = _invertIndexLib.find(word);
    if (it != _invertIndexLib.end()) {
      DF += it->second.size();  // DF: 包含该词的文档数
    }
    fprintf(stdout, "TF: %ld, DF: %ld, N: %ld\n", TF, DF, N);
    // IDF = log((N / (DF+1))+1)，逆文档频率，表示该词对于文档的重要性
    double IDF = log((1.0 * N / (DF + 1)) + 1);
    double w = TF * IDF;           // 权重w = TF * IDF
    double w_quadratic_sum = 0.0;  // 权重平方和
    for (auto& doc : it->second) {
      w_quadratic_sum += doc.second * doc.second;  // 累加平方和
    }
    // 归一化
    doc_w[word] = w / sqrt(w_quadratic_sum + w * w);
    fprintf(stdout, "doc_w[%s]: %lf, w: %lf\n", word.c_str(), doc_w[word], w);
  }

  // 计算余弦相似度, 并将结果存入优先队列排序
  priority_queue<pair<double, size_t>> result;
  for (auto& it : intersection) {
    size_t doc_id = it.first;
    double sim = 0.0;
    double w_quadratic_sum = 0.0;
    for (auto& word : words) {
      if (_invertIndexLib.find(word) == _invertIndexLib.end()) {
        continue;
      }
      sim += doc_w[word] * _invertIndexLib[word][doc_id].second;
      w_quadratic_sum += doc_w[word] * doc_w[word];
    }
    sim /= sqrt(w_quadratic_sum);
    result.push(make_pair(sim, doc_id));
  }

  // 取出前 WEB_PAGE_SEARCH_NUM 个结果
  fprintf(stdout, "search result size: %ld\n", result.size());
  size_t size =
      result.size() < WEB_PAGE_SEARCH_NUM ? result.size() : WEB_PAGE_SEARCH_NUM;
  for (size_t i = 0; i < size; ++i) {
    _webPages.push_back(result.top().second);
    fprintf(stdout, "doc_id: %ld, sim: %lf\n", result.top().second,
            result.top().first);
    result.pop();
  }
}

WebPage WebPageQuery::getWebPage(size_t doc_id) {
  auto it = _offsetLib.find(doc_id);
  if (it == _offsetLib.end()) {
    return WebPage(nullptr, 0);
  }
  string unique_page_lib_path =
      Configuration::getInstance()->getConfigMap(DATA)["UNIQUE_PAGE_LIB_PATH"];
  ifstream ifs(unique_page_lib_path);
  assert(ifs);
  string doc;
  ifs.seekg(it->second.first, std::ios::beg);
  // 读取文档
  doc.resize(it->second.second);
  ifs.read(&doc[0], it->second.second);
  ifs.close();
  // 解析网页
  XMLDocument document;
  document.Parse(doc.c_str(), doc.size());
  XMLElement* item_read = document.FirstChildElement("doc");
  WebPage page_read(item_read, doc_id);
  page_read.processDoc();
  return page_read;
}