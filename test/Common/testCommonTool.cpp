
#include <iostream>

#include "CommonTool.h"

using std::cout;
using std::endl;
using std::string;

void test_editDistance() {
  // std::string本身是一个字节流的字符串
  //  字符流的字符串
  string s1 = "abcd";  // 4个字符的字符串
  //获取的是字符的长度
  string s2 = "中国";  // 2个字符的字符串
  for (auto &ch : s2) {
    cout << ch;
  }
  cout << endl;
  cout << "s2[1]: " << s2[1] << endl;
  cout << endl;
  cout << "s1.size() : " << s1.size() << endl;
  cout << "s2.size() : " << s2.size() << endl;

  string s3 = s2.substr(0, 3);
  cout << "s3.size(): " << s3.size() << endl;
  cout << "s3: " << s3 << endl;

  string s4 = s2.substr(1, 3);
  cout << "s4.size(): " << s4.size() << endl;
  cout << "s4: " << s4 << endl;

  //字符的长度
  string s5 = "abc中国";
  cout << "s5.size(): " << s5.size() << endl;
  cout << "s5.length: " << length(s5) << endl;

  // 中国   => a中国 => ab中国 => abc中国
  // s2经过编辑之后，变成s5
  cout << "s2与s5的最小编辑距离: " << editDistance(s2, s5) << endl;
}

int main() {
  test_editDistance();
  return 0;
}
