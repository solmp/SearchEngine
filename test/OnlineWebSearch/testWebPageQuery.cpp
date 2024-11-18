#include "WebPageQuery.h"

int main() {
  Configuration::getInstance()->LoadConfig("../conf/config.json");
  WebPageQuery* p = WebPageQuery::getInstance();
  vector<size_t> webPages;
  p->doQuery("前期工作", webPages);
  for (auto& webPage : webPages) {
    WebPage page = p->getWebPage(webPage);
    fprintf(stdout, "doc_id: %ld\n", webPage);
    fprintf(stdout, "doc: %s\n\n", page.toJson().dump(2).c_str());
  }
  return 0;
}