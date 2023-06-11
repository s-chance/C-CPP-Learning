#include <algorithm>
#include <iostream>
#include <string>
using namespace std;

// 加法
string Plus(string a, string b) {
  int maxlen = max(a.length(), b.length());
  int *sum = new int[maxlen]();

  reverse(a.begin(), a.end());
  reverse(b.begin(), b.end());

  for (int i = 0; i < maxlen; i++) {
    int a_bit = 0;
    int b_bit = 0;
    if (i < a.length()) {
      a_bit = stoi(string(1, a.at(i)));
    }
    if (i < b.length()) {
      b_bit = stoi(string(1, b.at(i)));
    }

    sum[i] += (a_bit + b_bit);
    if (i < maxlen - 1 && sum[i] > 9) {
      sum[i + 1] = sum[i] / 10;
      sum[i] %= 10;
    }
  }

  string res = "";
  bool zeroStrat = true;
  for (int i = maxlen - 1; i >= 0; i--) {
    if (sum[i] == 0 && zeroStrat) {
      continue;
    }
    zeroStrat = false;
    res.append(to_string(sum[i]));
  }
  return res;
}

// 减法
string Substarct(string a, string b) {
  int maxlen = max(a.length(), b.length());
  int *sum = new int[maxlen]();

  reverse(a.begin(), a.end());
  reverse(b.begin(), b.end());

  // 对 a < b 的情况特别处理
  string flag = "";
  if (a.length() < b.length()) {
    flag = "-";
    swap(a, b);
  } else if (a.length() == b.length()) {
    for (int i = 0; i < a.length(); i++) {
      if (a[i] > b[i]) {
        break;
      }
      if (a[i] < b[i]) {
        flag = "-";
        swap(a, b);
        break;
      }
    }
  }

  for (int i = 0; i < maxlen; i++) {
    int a_bit = 0;
    int b_bit = 0;
    if (i < a.length()) {
      a_bit = stoi(string(1, a.at(i)));
    }
    if (i < b.length()) {
      b_bit = stoi(string(1, b.at(i)));
    }

    sum[i] += (a_bit - b_bit);
    if (i < maxlen - 1 && sum[i] < 0) {
      sum[i + 1] = sum[i + 1] - 1;
      sum[i] += 10;
    }
  }

  string res = "";
  bool zeroStart = true;
  for (int i = maxlen - 1; i >= 0; i--) {
    if (sum[i] == 0 && zeroStart) {
      continue;
    }
    zeroStart = false;
    res.append(to_string(sum[i]));
  }
  return flag + res;
}

// 乘法
string Multiply(string a, string b) {
  if (a.length() < 2 && b.length() < 2) {
    int ai = stoi(a);
    int bi = stoi(b);
    return to_string(ai * bi);
  }

  int a_halflen = a.length() / 2;
  int b_halflen = b.length() / 2;

  string ahead = "0";
  string atail = "0";

  if (a.length() > a_halflen && a_halflen > 0) {
    ahead = a.substr(0, a_halflen);
    atail = a.substr(a_halflen, a.length() - a_halflen);
  } else {
    ahead = "0";
    atail = a;
  }

  string bhead = "0";
  string btail = "0";

  if (b.length() > b_halflen && b_halflen > 0) {
    bhead = b.substr(0, b_halflen);
    btail = b.substr(b_halflen, b.length() - b_halflen);
  } else {
    bhead = "0";
    btail = b;
  }

  string ahbh = Multiply(ahead, bhead);
  string atbt = Multiply(atail, btail);
  string ahbt = Multiply(ahead, btail);
  string atbh = Multiply(atail, bhead);

  ahbh.append((a.length() - a_halflen) + (b.length() - b_halflen), '0');
  ahbt.append(a.length() - a_halflen, '0');
  atbh.append(b.length() - b_halflen, '0');

  string res = "";
  res = Plus(ahbh, ahbt);
  res = Plus(res, atbh);
  res = Plus(res, atbt);

  return res;
}

// 结果的符号位
string flagPos(string &a, string &b, char &method) {
  string flag = "";  // 符号，默认为正
  // 均为正数，只需要考虑减法结果是否可能为负
  if (a[0] == b[0] && a[0] != '-' && method == '-') {
    if (a.length() == b.length()) {
      // 从高位依次比较字符大小
      for (int i = 0; i < a.length(); i++) {
        // 只有在位相等的时候才会继续循环，否则直接跳出循环
        // 目的是在对某个位比较时，确保前面的位是相等的
        if (a[i] > b[i]) {
          break;  // a的高位大于b直接跳出循环
        }
        if (a[i] < b[i]) {
          flag = "-";
          break;  // a的高位小于b，修改符号，跳出循环
        }
      }
    }
    // 如果b的位数大于a，而不是等于a，则直接将符号修改为负
    if (a.length() < b.length()) {
      flag = "-";
    }
    return flag;
  }
  // a为正，b为负，只需要考虑加法结果是否可能为负
  // 这里考虑将 a + (-b) 转化为 a - b 处理
  if (a[0] != b[0] && b[0] == '-' && method == '+') {
    // 对b进行处理，得到b的无符号数
    b = b.substr(1, b.length() - 1);
    method = '-';  // 修改为减法
    flag = flagPos(a, b, method);
    return flag;
  } else if (a[0] != b[0] && b[0] == '-' && method == '*') {
    flag = "-";  // 乘法一定为负
    // 将 a * (-b) 转化为 - (a * b)
    b = b.substr(1, b.length() - 1);
    return flag;
  } else if (a[0] != b[0] && b[0] == '-' && method == '-') {
    flag = "";  // 减法一定为正
    // 将 a - (-b) 转化为 a + b
    b = b.substr(1, b.length() - 1);
    method = '+';  // 修改为加法
    return flag;
  }
  // 同理
  // a为负，b为正，只需要考虑加法结果是否可能为负
  // 这里考虑将 -a + b 转化为 b - a 处理
  if (a[0] != b[0] && a[0] == '-' && method == '+') {
    // 对a进行处理，得到a的无符号数
    a = a.substr(1, a.length() - 1);
    method = '-';  // 修改为减法
    swap(a, b);    // 交换a，b的值
    flag = flagPos(a, b, method);
    return flag;
  } else if (a[0] != b[0] && a[0] == '-' && method == '*') {
    flag = "-";  // 乘法一定为负
    // 将 -a * b 转化为 - (a * b)
    a = a.substr(1, a.length() - 1);
    return flag;
  } else if (a[0] != b[0] && a[0] == '-' && method == '-') {
    flag = "-";  // 减法一定为负
    // 将 -a - b 转化为 - (a + b)
    a = a.substr(1, a.length() - 1);
    method = '+';  // 修改为加法
    return flag;
  }

  // 均为负数，只需要考虑减法结果是否可能为负
  // 这里考虑将 (-a) - (-b) 转化为 b - a
  if (a[0] == b[0] && a[0] == '-' && method == '-') {
    // 对a，b进行处理，得到a，b的无符号数
    a = a.substr(1, a.length() - 1);
    b = b.substr(1, b.length() - 1);
    swap(a, b);  // 交换a，b的值
    flag = flagPos(a, b, method);
    return flag;
  } else if (a[0] == b[0] && a[0] == '-' && method == '*') {
    flag = "";  // 乘法一定为正
    // 将 (-a) * (-b) 转化为 a * b
    a = a.substr(1, a.length() - 1);
    b = b.substr(1, b.length() - 1);
    return flag;
  } else if (a[0] == b[0] && a[0] == '-' && method == '+') {
    flag = "-";  // 加法一定为负
    // 将 (-a) + (-b) 转化为 - (a + b)
    a = a.substr(1, a.length() - 1);
    b = b.substr(1, b.length() - 1);
    method = '+';
    return flag;
  }
  return flag;
}

string Calculate(string a, string b, char method) {
  string res;

  res = flagPos(a, b, method);

  if (method == '+') {
    res += Plus(a, b);
  }
  if (method == '-') {
    res += Substarct(a, b);
  }
  if (method == '*') {
    res += Multiply(a, b);
  }
  if (res == "") {
    res = "0";
  }
  return res;
}

bool isNum(string s) {
  for (int i = 0; i < s.length(); i++) {
    if (s[i] > '9' || s[i] < '0') {
      return false;
    }
  }
  return true;
}
bool isMethod(char method) {
  if (method != '+' && method != '-' && method != '*') {
    return false;
  }
  return true;
}

int main() {
  string a, b;
  char method;
  while (cin >> a >> b >> method) {
    if (!isNum(a + b)) {
      cout << "不是数字!" << endl;
      continue;
    }
    if (!isMethod(method)) {
      cout << "不支持的运算符号!" << endl;
      continue;
    }
    string res = Calculate(a, b, method);
    cout << res << endl;
  }
}
