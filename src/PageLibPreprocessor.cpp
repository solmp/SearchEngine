#include "PageLibPreprocessor.h"

PageLibPreprocessor::PageLibPreprocessor(Configuration* config, SplitTool* tool)
    : _conf(config), _wordCutter(tool) {}

void PageLibPreprocessor::readOldOffsetLib() {
  // 读取网页偏移库
  string page_offset_path = _conf->getConfigMap(DATA)["PAGE_OFFSET_PATH"];
  fprintf(stderr, "page_offset_path: %s\n", page_offset_path.c_str());
  ifstream ifs(page_offset_path);
  if (!ifs) {
    throw std::runtime_error("ifstream open file error!");
  }
  string line;
  size_t doc_id, offset, size;
  while (std::getline(ifs, line)) {
    sscanf(line.c_str(), "%ld %ld %ld", &doc_id, &offset, &size);
    _offsetLib[doc_id] = std::make_pair(offset, size);
  }
  ifs.close();
  fprintf(stderr, "page_size: %ld\n", _offsetLib.size());
}

void PageLibPreprocessor::getSimhashFigure(
    unordered_map<size_t, uint64_t>& simhashLib) {
  // 初始化simhasher
  json& split_tool_conf = _conf->getConfigMap(SPLIT_TOOL);
  Simhasher simhasher(split_tool_conf["DICT_PATH"], split_tool_conf["HMM_PATH"],
                      split_tool_conf["USER_DICT_PATH"],
                      split_tool_conf["IDF_PATH"],
                      split_tool_conf["STOP_WORD_PATH"]);

  // 读取网页库, 获取文档指纹
  ifstream ifs(_conf->getConfigMap(DATA)["PAGE_LIB_PATH"]);
  assert(ifs);
  for (auto& it : _offsetLib) {
    size_t doc_id = it.first;
    off_t offset = it.second.first;
    size_t size = it.second.second;
    string doc;
    ifs.seekg(offset, std::ios::beg);
    // 读取文档
    doc.resize(size);
    ifs.read(&doc[0], size);

    // 解析文档
    XMLDocument node;
    node.Parse(doc.c_str(), size);
    XMLElement* item = node.FirstChildElement("doc");
    WebPage web_page(item, doc_id);
    web_page.processDoc();
    // 计算文档指纹
    uint64_t u64 = 0;
    simhasher.make(web_page.getDocContent(), TOP_N, u64);
    simhashLib[doc_id] = u64;
  }
  ifs.close();
  fprintf(stderr, "simhash_size: %ld\n", simhashLib.size());
}

void PageLibPreprocessor::cutRedundantPage() {
  readOldOffsetLib();
  unordered_map<size_t, uint64_t> simhashLib;  // 存储文档指纹
  getSimhashFigure(simhashLib);

  // 比较相似度，去重
  auto it_slow = simhashLib.begin();
  while (it_slow != simhashLib.end()) {
    auto it_fast = it_slow;
    ++it_fast;
    while (it_fast != simhashLib.end()) {
      if (Simhasher::isEqual(it_slow->second, it_fast->second)) {
        _offsetLib.erase(it_fast->first);
        it_fast = simhashLib.erase(it_fast);
      } else {
        ++it_fast;
      }
    }
    ++it_slow;
  }
  fprintf(stderr, "new_page_size: %ld\n", _offsetLib.size());

  // 保存去重后的网页库
  ifstream ifs(_conf->getConfigMap(DATA)["PAGE_LIB_PATH"]);
  assert(ifs);
  ofstream ofs(_conf->getConfigMap(DATA)["NEW_PAGE_LIB_PATH"]);
  assert(ofs);
  off_t new_offset = 0;
  for (auto& it : _offsetLib) {
    size_t doc_id = it.first;
    off_t offset = it.second.first;
    size_t size = it.second.second;
    string doc;
    ifs.seekg(offset, std::ios::beg);
    doc.resize(size);
    ifs.read(&doc[0], size);
    ofs << doc;
    _offsetLib[doc_id].first = new_offset;
    new_offset += size;
  }
  ofs.close();
  ifs.close();

  // 保存去重后的网页偏移库
  ofstream ofs_offset(_conf->getConfigMap(DATA)["NEW_PAGE_OFFSET_PATH"]);
  assert(ofs_offset);
  for (auto& it : _offsetLib) {
    ofs_offset << it.first << " " << it.second.first << " " << it.second.second
               << '\n';
  }
  ofs_offset.close();
}

void PageLibPreprocessor::bulidInvertIndexMap() { return; }

void PageLibPreprocessor::storeOnDisk() { return; }