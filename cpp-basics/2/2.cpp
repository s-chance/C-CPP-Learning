#include <iostream>
#include <string>
using namespace std;

int main() {
  // 测试用例一
  // 12131 !!#@$@$@ jdhhsbcdsjhGGDJASDJH
  // 测试用例二
  // Life is too short to spend time with people who suck the happiness out of
  // you. If someone wants you in their life, they’ll make room for you. You
  // shouldn’t have to fight for a spot. Never, ever insist yourself to someone
  // who continuously overlooks your worth. And remember, it’s not the people
  // that stand by your side when you’re at your best, but the ones who stand
  // beside you when you’re at your worst that are your true friends.

  string str;

  int upper = 0, lowwer = 0, math = 0, space = 0, others = 0;
  int words = 0;
  while (getline(cin, str)) {
    int len = str.length();
    if (len == 0) {
      break;
    }
    if (str[len - 1] != ' ') {
      words = 1;  // 初始化单词数为1
    }
    bool eow = false;
    while (len--) {
      if (str[len] <= 'Z' && str[len] >= 'A') {
        upper++;
        eow = true;
      } else if (str[len] <= 'z' && str[len] >= 'a') {
        lowwer++;
        eow = true;
      } else if (str[len] <= '9' && str[len] >= '0') {
        math++;
        eow = true;
      } else if (str[len] == ' ') {
        space++;
        if (eow == true) {
          words++;
          eow = false;
        }
      } else {
        others++;
        eow = true;
      }
    }
  }

  cout << "大写字母: " << upper << endl;
  cout << "小写字母: " << lowwer << endl;
  cout << "数字字符: " << math << endl;
  cout << "空格: " << space << endl;
  cout << "其他字符: " << others << endl;
  cout << "单词数: " << words << endl;
}