#include "PageLib.h"

PageLib::PageLib(Configuration *config) : _config(config) {
  // 获取语料库中的所有xml文件路径
  DirScanner scanner;
  string page_corpus_path = _config->getConfigMap(ASSETS)["PAGE_CORPUS_PATH"];
  scanner.traversePath(page_corpus_path);
  _pagesPath = std::move(scanner.getFiles());
}

void PageLib::create() {
  // 遍历语料库中的每一个xml网页文件
  off_t offset = 0;
  size_t doc_id = 0;
  const string page_lib_path = _config->getConfigMap(DATA)["PAGE_LIB_PATH"];

  // 打开输出文件
  ofstream ofs(page_lib_path);
  for (const string &pagePath : _pagesPath) {
    // 读取xml文件
    XMLDocument doc;
    doc.LoadFile(pagePath.c_str());
    if (doc.ErrorID() != tinyxml2::XML_SUCCESS) {
      fprintf(stderr, "Load Error: %d\n", doc.ErrorID());
      throw std::runtime_error("LoadXML Error");
    }
    // 找到文章的根节点
    XMLElement *node =
        doc.FirstChildElement("rss")->FirstChildElement("channel");
    size_t size = node->ChildElementCount("item");

    // 遍历每一个item节点，生成WebPage对象
    node = node->FirstChildElement("item");
    for (size_t i = 0; i < size; i++) {
      if (node == nullptr) return;
      WebPage page(node, doc_id);
      page.processDoc();                        // 处理文档
      page.dump(ofs);                           // 将WebPage对象写入文件
      node = node->NextSiblingElement("item");  // 下一个item节点
      // 保存WebPage对象偏移量和大小
      size_t page_size = page.getDocSize();
      if (page_size == 0) {
        continue;
      }
      _offsetLib[doc_id] = std::make_pair(offset, page_size);
      // 更新偏移量和文档id
      offset += page_size;
      ++doc_id;
    }
  }
  ofs.close();
}

void PageLib::store() {
  // 将偏移库写入文件
  string page_offset_path = _config->getConfigMap(DATA)["PAGE_OFFSET_PATH"];
  ofstream ofs(page_offset_path);
  for (auto &p : _offsetLib) {
    ofs << p.first << " " << p.second.first << " " << p.second.second << '\n';
  }
}