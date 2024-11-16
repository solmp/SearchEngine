#include "WebPage.h"

int main() {
  string xml_text = R"(
        <item>
            <title><![CDATA[title1]]></title>
            <link>link1</link>
            <description><![CDATA[content1]]></description>
            <pubDate>2021-05-18 17:28:13</pubDate>
            <source><![CDATA[来源：人民网-读书频道]]></source>
            <author><![CDATA[作者：]]></author>
            <category><![CDATA[图书]]></category>
            <guid isPermaLink="true">http://book.people.cn/n1/2021/0518/c69323-32133107.html</guid>

        </item>
        <item>
            <title><![CDATA[title2]]></title>
            <link>link2</link>
            <description><![CDATA[content2]]></description>
            <pubDate>2021-05-18 17:28:13</pubDate>
            <source><![CDATA[来源：人民网-读书频道]]></source>
            <author><![CDATA[作者：]]></author>
            <category><![CDATA[图书]]></category>
            <guid isPermaLink="true">http://book.people.cn/n1/2021/0518/c69323-32133107.html</guid>
        </item>
  )";
  XMLDocument doc;
  doc.Parse(xml_text.c_str());
  XMLElement* node = doc.FirstChildElement("item");
  fprintf(stderr, "node: %s\n", node->Name());
  WebPage page(node, 0);
  page.processDoc();
  ofstream ofs("page.xml");
  page.dump(ofs);
  ofs.close();
  fprintf(stderr, "page_size: %ld\n", page.getDocSize());

  ifstream ifs("page.xml");
  ifs.seekg(0, std::ios::beg);
  string doc_read;
  doc_read.resize(page.getDocSize());
  ifs.read(&doc_read[0], page.getDocSize());
  fprintf(stderr, "[%s], size: %ld\n", doc_read.c_str(),
          strlen(doc_read.c_str()));

  XMLDocument node_read;
  node_read.Parse(doc_read.c_str(), page.getDocSize());
  XMLElement* item_read = node_read.FirstChildElement("doc");
  WebPage page_read(item_read, page.getDocId());
  page_read.processDoc();
  fprintf(stderr, "title: %s\n", page_read.getTile().c_str());
  return 0;
}