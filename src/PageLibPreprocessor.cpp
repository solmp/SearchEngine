#include "PageLibPreprocessor.h"

PageLibPreprocessor::PageLibPreprocessor(Configuration* config, SplitTool* tool)
    : _conf(config), _wordCutter(tool) {}

void PageLibPreprocessor::readOldOffsetLib() {
  // 读取网页偏移库
  string page_offset_path = _conf->getConfigMap(DATA)["PAGE_OFFSET_PATH"];
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
  readOldOffsetLib();
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
  ofstream ofs_page(_conf->getConfigMap(DATA)["NEW_PAGE_LIB_PATH"]);
  assert(ofs_page);
  // 保存去重后的网页偏移库
  ofstream ofs_offset(_conf->getConfigMap(DATA)["NEW_PAGE_OFFSET_PATH"]);
  assert(ofs_offset);

  off_t new_offset = 0;
  size_t new_id = 0;
  for (auto& it : _offsetLib) {
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
    WebPage web_page(node.FirstChildElement("doc"), new_id);
    web_page.processDoc();
    // 计算文档指纹
    uint64_t u64 = 0;
    simhasher.make(web_page.getDocContent(), TOP_N, u64);
    // 去重
    auto check_it = simhashFigure.begin();
    for (; check_it != simhashFigure.end(); ++check_it) {
      if (Simhasher::isEqual(check_it->second, u64)) {
        break;
      }
    }
    if (check_it == simhashFigure.end()) {
      simhashFigure[new_id] = u64;
      web_page.dump(ofs_page);
      ofs_offset << new_id << " " << new_offset << " " << size << '\n';
      new_offset += size;
      ++new_id;
    }
  }
  ofs_offset.close();
  ofs_page.close();
  ifs.close();
  fprintf(stderr, "simhash_size: %ld\n", simhashFigure.size());
}

void PageLibPreprocessor::bulidInvertIndexMap() { return; }

void PageLibPreprocessor::storeOnDisk() { return; }