#include <iostream>
using namespace std;

// 从from串中的startpos位置开始拷贝len个字符串内容到to串中，返回拷贝是否成功的信息(失败情况如位置无效，长度无效等)
bool mystrncpy(char *to, char *form, unsigned startpos, unsigned len);

bool mystrncpy(char *to, char *form, unsigned startpos, unsigned len) {
  if (len < 0 || startpos < 0) {
    return false;
  }

  for (int i = 0; i < len; i++) {
    to[i] = form[startpos + i];
  }
  return true;
}

int main() {
  string str = "abcdefghijklmn";
  char *form = new char[str.length()]();
  char *to = new char[str.length()]();
  form = &str[0];

  cout << mystrncpy(to, form, 0, 0) << endl;
  cout << "form: " << form << endl;
  cout << "to: " << to << endl;

  cout << mystrncpy(to, form, 3, 4) << endl;
  cout << "form: " << form << endl;
  cout << "to: " << to << endl;
  cout << mystrncpy(to, form, 3, 20) << endl;

  cout << "form: " << form << endl;
  cout << "to: " << to << endl;
}