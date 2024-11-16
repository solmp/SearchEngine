#include "PageLibPreprocessor.h"

PageLibPreprocessor::PageLibPreprocessor(Configuration* config, SplitTool* tool)
    : _conf(config), _wordCutter(tool) {}

void PageLibPreprocessor::readOldOffsetLib(const string& page_offset_path) {
  _offsetLib.clear();
  // 读取网页偏移库
  fprintf(stderr, "page_offset_path: %s\n", page_offset_path.c_str());
  ifstream ifs(page_offset_path);
  assert(ifs);
  string line;
  size_t doc_id, offset, size;
  while (std::getline(ifs, line)) {
    sscanf(line.c_str(), "%ld %ld %ld", &doc_id, &offset, &size);
    _offsetLib[doc_id] = std::make_pair(offset, size);
  }
  ifs.close();
  fprintf(stderr, "page_size: %ld\n", _offsetLib.size());
}

void PageLibPreprocessor::cutRedundantPage() {
  string page_offset_path = _conf->getConfigMap(DATA)["PAGE_OFFSET_PATH"];
  readOldOffsetLib(page_offset_path);
  // 初始化simhasher
  json& split_tool_conf = _conf->getConfigMap(SPLIT_TOOL);
  Simhasher simhasher(split_tool_conf["DICT_PATH"], split_tool_conf["HMM_PATH"],
                      split_tool_conf["USER_DICT_PATH"],
                      split_tool_conf["IDF_PATH"],
                      split_tool_conf["STOP_WORD_PATH"]);
  unordered_map<size_t, uint64_t> simhashFigure;  // 存储文档指纹

  // 读取网页库, 获取文档指纹
  ifstream ifs(_conf->getConfigMap(DATA)["PAGE_LIB_PATH"]);
  assert(ifs);
  // 保存去重后的网页库
  ofstream ofs_page(_conf->getConfigMap(DATA)["UNIQUE_PAGE_LIB_PATH"]);
  assert(ofs_page);
  // 保存去重后的网页偏移库
  ofstream ofs_offset(_conf->getConfigMap(DATA)["UNIQUE_PAGE_OFFSET_PATH"]);
  assert(ofs_offset);

  off_t new_offset = 0;
  for (auto& it : _offsetLib) {
    size_t doc_id = it.first;
    off_t offset = it.second.first;
    size_t size = it.second.second;
    string doc;
    ifs.seekg(offset, std::ios::beg);
    // 读取文档
    doc.resize(size);
    ifs.read(&doc[0], size);
    // 计算文档指纹
    uint64_t u64 = 0;
    simhasher.make(doc, TOP_N, u64);
    // 去重
    auto check_it = simhashFigure.begin();
    for (; check_it != simhashFigure.end(); ++check_it) {
      if (Simhasher::isEqual(check_it->second, u64)) {
        break;
      }
    }
    // 如果没有找到相同的文档指纹，则将其保存到新的网页库和网页偏移库中
    if (check_it == simhashFigure.end()) {
      simhashFigure[doc_id] = u64;
      ofs_page << doc;
      ofs_offset << doc_id << " " << new_offset << " " << size << '\n';
      new_offset += size;
    }
  }
  ofs_offset.close();
  ofs_page.close();
  ifs.close();
  fprintf(stderr, "simhash_size: %ld\n", simhashFigure.size());
}

void PageLibPreprocessor::bulidInvertIndexMap(
    unordered_set<string>& stop_words) {
  // 读取去重网页偏移库
  string page_offset_path =
      _conf->getConfigMap(DATA)["UNIQUE_PAGE_OFFSET_PATH"];
  readOldOffsetLib(page_offset_path);

  // 用于读取文档
  ifstream ifs_page(_conf->getConfigMap(DATA)["UNIQUE_PAGE_LIB_PATH"]);
  assert(ifs_page);
  size_t N = 0;  // N: 网页库文档总数
  // DF: 包含该词的文档数
  // TF: 该词在文档中出现的次数 map<单词, 所在文档id集合<文档id, 词频>>
  unordered_map<string, vector<pair<size_t, size_t>>> DFTF;
  // 遍历去重后的网页库，网页分词得到DFTF
  for (auto& it : _offsetLib) {
    size_t doc_id = it.first;
    off_t offset = it.second.first;
    size_t size = it.second.second;
    // 读取文档
    string doc;
    ifs_page.seekg(offset, std::ios::beg);
    doc.resize(size);
    ifs_page.read(&doc[0], size);
    // 分词
    vector<string> words;
    _wordCutter->cut(doc, words);
    // 统计词频
    unordered_map<string, size_t> wordFreq;
    for (auto& word : words) {
      wordFreq[word]++;
    }
    // 保存到DFTF
    for (auto& word : wordFreq) {
      if (stop_words.find(word.first) != stop_words.end()) {
        continue;
      }
      DFTF[word.first].emplace_back(std::make_pair(doc_id, word.second));
    }
    ++N;
  }
  ifs_page.close();

  // 生成倒排索引
  for (auto& it : DFTF) {
    string word = it.first;
    size_t DF = it.second.size();  // DF: 包含该词的文档数
    // IDF = log((N / (DF+1))+1)，逆文档频率，表示该词对于文档的重要性
    double IDF = log((1.0 * N / (DF + 1)) + 1);
    double w_quadratic_sum = 0.0;         // 权重平方和
    unordered_map<size_t, double> doc_w;  // 用于保存权重
    for (auto& doc : it.second) {
      size_t doc_id = doc.first;  // 文档编号
      size_t TF = doc.second;     // TF：该词在文档中出现的次数
      double w = TF * IDF;        // 权重w = TF * IDF
      doc_w[doc_id] = w;          // 保存权重
      w_quadratic_sum += w * w;   // 累加平方和
    }
    // 归一化 w = w / sqrt(w1^2 + w2^2 + ... + wn^2)
    _invertIndexLib[word].reserve(it.second.size());
    for (auto& doc : it.second) {
      size_t doc_id = doc.first;
      double w = doc_w[doc_id];
      w /= sqrt(w_quadratic_sum);
      _invertIndexLib[word].emplace_back(std::make_pair(doc_id, w));
    }
  }
}

void PageLibPreprocessor::storeOnDisk() {
  // 获取倒排索引保存路径
  string invert_index_path = _conf->getConfigMap(DATA)["INVERT_INDEX_PATH"];
  ofstream ofs(invert_index_path);
  assert(ofs);
  // 保存倒排索引
  for (auto& it : _invertIndexLib) {
    ofs << it.first << " ";
    for (auto& doc : it.second) {
      ofs << doc.first << " " << doc.second << " ";
    }
    ofs << '\n';
  }
  ofs.close();
}