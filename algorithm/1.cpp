#include <chrono>
#include <iostream>
using namespace std;
using namespace chrono;

string temp[1000];

// 最多只能准确计算到第110位斐波那契数列
string add(string a, string b) {
  int maxlen = 0;
  a.length() >= b.length() ? maxlen = a.length() : maxlen = b.length();
  // 补零统一长度
  while (a.length() < maxlen + 1) {
    a = "0" + a;
  }
  while (b.length() < maxlen + 1) {
    b = "0" + b;
  }
  char *res = new char[maxlen + 1](),
       *tmp = new char[maxlen + 1]();  // 考虑最大位进位的情况
  int i;
  for (i = 0; i < maxlen;) {
    int an = a[maxlen - i] - 48;
    int bn = b[maxlen - i] - 48;
    int sum = an + bn;
    tmp[i] = (char)(sum % 10 + 48);
    while (sum >= 10) {
      i++;
      if (i >= maxlen) {
        tmp[i] = '1';
        break;
      }
      an = a[maxlen - i] - 48;
      bn = b[maxlen - i] - 48;
      sum = an + bn + 1;
      tmp[i] = (char)(sum % 10 + 48);
    }
    i++;
  }
  maxlen = i;
  for (int j = maxlen - 1; j >= 0; j--) {
    res[maxlen - 1 - j] = tmp[j];
  }
  return res;
}

// 非递归实现斐波那契
string fibonacci(int n) {
  if (n == 0) {
    return "0";
  }
  if (n <= 2) {
    return "1";
  }
  string ans = "2", t = "1";
  for (int i = 3; i < n; i++) {
    string tmp = ans;
    ans = add(ans, t);
    t = tmp;
  }
  return ans;
}

// 递归实现斐波那契
string fibonacci_2(int n) {
  if (n == 0) {
    return "0";
  }
  if (n <= 2) {
    return "1";
  }
  return add(fibonacci_2(n - 1), fibonacci_2(n - 2));
}

// 递归优化
string fibonacci_3(int n) {
  if (n == 0) {
    return "0";
  }
  if (n <= 2) {
    return "1";
  }
  if (temp[n] != "") {
    return temp[n];
  }
  temp[n] = add(fibonacci_3(n - 1), fibonacci_3(n - 2));
  return temp[n];
}

int main() {
  cout << "Please input the number to calculate: ";
  int n;
  cin >> n;

  auto start = system_clock::now();
  cout << "非递归实现: " << fibonacci(n) << endl;
  duration<double> diff = system_clock::now() - start;
  cout << "用时 " << diff.count() * 1000 << " 毫秒" << endl;

  start = system_clock::now();
  cout << "递归优化实现: " << fibonacci_3(n) << endl;
  diff = system_clock::now() - start;
  cout << "用时 " << diff.count() * 1000 << " 毫秒" << endl;

  start = system_clock::now();
  cout << "递归普通实现: " << fibonacci_2(n) << endl;
  diff = system_clock::now() - start;
  cout << "用时 " << diff.count() * 1000 << " 毫秒" << endl;

  return 0;
}