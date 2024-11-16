/**
 * @brief 网页类
 */

#include "WebPage.h"

// HTML 实体编码映射表
static unordered_map<string, char32_t> htmlEntities = {
    {"&lt;", U'<'},   {"&gt;", U'>'},    {"&amp;", U'&'},
    {"&quot;", U'"'}, {"&apos;", U'\''},
};

WebPage::WebPage(XMLElement *item, size_t doc_id)
    : _doc(item), _docId(doc_id) {}

// 去除头尾空格
void trim(string &str) {
  str.erase(0, str.find_first_not_of(" \t\n\r"));
  str.erase(str.find_last_not_of(" \t\n\r") + 1);
}

void WebPage::processDoc() {
  string description = "";
  string contentEncoded = "";
  string content = "";
  XMLElement *node = _doc->FirstChildElement("title");
  if (node != nullptr) {
    _docTitle = node->GetText();
  }
  node = _doc->FirstChildElement("link");
  if (node != nullptr) {
    _docUrl = node->GetText();
  }
  node = _doc->FirstChildElement("description");
  if (node != nullptr) {
    description = node->GetText();
  }
  node = _doc->FirstChildElement("content:encoded");
  if (node != nullptr) {
    contentEncoded = node->GetText();
  }
  node = _doc->FirstChildElement("content");
  if (node != nullptr) {
    content = node->GetText();
  }

  _docContent = contentEncoded.empty() ? content : contentEncoded;
  if (_docContent.empty()) {
    _docContent = description;
  }

  regex tagRegex("<[^>]*>");
  _docContent = regex_replace(_docContent, tagRegex, "");
  // _docContent = decodeHtmlEntities(_docContent); // 解码 HTML 实体

  // 去除头尾空白字符
  trim(_docTitle);
  trim(_docUrl);
  trim(_docContent);
}

string WebPage::decodeHtmlEntities(const string &input) {
  string output;
  std::regex entityRegex(R"(&[a-zA-Z0-9#]+;)");
  std::sregex_iterator it(input.begin(), input.end(), entityRegex);
  std::sregex_iterator end;

  size_t lastPos = 0;

  while (it != end) {
    // 获取匹配的实体
    string entity = it->str();

    // 将前面的文本添加到输出
    output.append(input.substr(lastPos, it->position() - lastPos));

    // 查找该实体的对应字符
    if (htmlEntities.find(entity) != htmlEntities.end()) {
      output += static_cast<char>(htmlEntities[entity]);  // 添加对应字符
    } else if (entity[1] == '#') {                        // 处理数字实体
      // 处理十进制和十六进制
      char32_t codePoint = 0;
      if (entity[2] == 'x' || entity[2] == 'X') {
        codePoint =
            std::stoul(entity.substr(3, entity.size() - 4), nullptr, 16);
      } else {
        codePoint = std::stoul(entity.substr(2, entity.size() - 3));
      }

      // 将字符追加到输出中，使用 UTF-8 编码
      if (codePoint <= 0x7F) {
        output += static_cast<char>(codePoint);
      } else if (codePoint <= 0x7FF) {
        output += static_cast<char>((codePoint >> 6) | 0xC0);
        output += static_cast<char>((codePoint & 0x3F) | 0x80);
      } else if (codePoint <= 0xFFFF) {
        output += static_cast<char>((codePoint >> 12) | 0xE0);
        output += static_cast<char>(((codePoint >> 6) & 0x3F) | 0x80);
        output += static_cast<char>((codePoint & 0x3F) | 0x80);
      } else if (codePoint <= 0x10FFFF) {
        output += static_cast<char>((codePoint >> 18) | 0xF0);
        output += static_cast<char>(((codePoint >> 12) & 0x3F) | 0x80);
        output += static_cast<char>(((codePoint >> 6) & 0x3F) | 0x80);
        output += static_cast<char>((codePoint & 0x3F) | 0x80);
      }
    }

    lastPos = it->position() + it->length();  // 更新上一个位置
    ++it;
  }

  // 添加最后部分的文本
  output.append(input.substr(lastPos));
  std::sregex_iterator it_check(input.begin(), input.end(), entityRegex);
  if (it_check != end) {
    return decodeHtmlEntities(output);
  }
  return output;
}

void WebPage::dump(ofstream &ofs) {
  if (_docTitle.empty() || _docUrl.empty() || _docContent.empty()) {
    return;
  }
  XMLDocument document;
  XMLElement *doc = document.NewElement("doc");
  document.InsertEndChild(doc);

  XMLElement *docid = document.NewElement("docid");
  XMLElement *title = document.NewElement("title");
  XMLElement *link = document.NewElement("link");
  XMLElement *content = document.NewElement("content");
  doc->InsertEndChild(docid);
  doc->InsertEndChild(title);
  doc->InsertEndChild(link);
  doc->InsertEndChild(content);

  docid->SetText(_docId);
  title->SetText(_docTitle.c_str());
  link->SetText(_docUrl.c_str());

  XMLText *content_text = document.NewText(_docContent.c_str());
  content_text->SetCData(true);
  content->InsertEndChild(content_text);

  // 将文档保存到文件
  tinyxml2::XMLPrinter printer;
  document.Print(&printer);
  _docSize = printer.CStrSize() - 1;
  ofs << printer.CStr();
}

bool operator<(const WebPage &lhs, const WebPage &rhs) {
  return lhs._docId < rhs._docId;
}