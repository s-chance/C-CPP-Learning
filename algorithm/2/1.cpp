#include <algorithm>
#include <chrono>
#include <iostream>
using namespace std;
using namespace chrono;

string add(string a, string b) {
  int maxlen = max(a.length(), b.length());
  int *sum = new int[maxlen]();

  reverse(a.begin(), a.end());
  reverse(b.begin(), b.end());

  for (int i = 0; i < maxlen; i++) {
    int a_bit = 0;
    int b_bit = 0;
    if (i < a.length()) {
      // string(num, c) 生成一个字符串，包含num个c字符
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
  bool zeroStart = true;
  for (int i = maxlen - 1; i >= 0; i--) {
    if (sum[i] == 0 && zeroStart) {
      continue;
    }
    zeroStart = false;
    res.append(to_string(sum[i]));
  }
  return res;
}

string cal(string a, string b) {
  // 规模足够小直接返回结果
  if (a.length() < 2 && b.length() < 2) {
    int ai = stoi(a);
    int bi = stoi(b);
    return to_string(ai * bi);
  }

  // 长度对半分
  int ahalflen = a.length() / 2;
  int bhalflen = b.length() / 2;

  // 大整数分成前半部分和后半部分
  string ahead = "0";
  string atail = "0";

  if (a.length() > ahalflen && ahalflen > 0) {
    // substr(pos, len) 截取一个字符串从pos位置开始，长度为len的部分
    ahead = a.substr(0, ahalflen);
    atail = a.substr(ahalflen, a.length() - ahalflen);
  } else {
    ahead = "0";
    atail = a;
  }

  string bhead = "0";
  string btail = "0";
  if (b.length() > bhalflen && bhalflen > 0) {
    bhead = b.substr(0, bhalflen);
    btail = b.substr(bhalflen, b.length() - bhalflen);
  } else {
    bhead = "0";
    btail = b;
  }

  string ahbh = cal(ahead, bhead);
  string atbt = cal(atail, btail);
  string ahbt = cal(ahead, btail);
  string atbh = cal(atail, bhead);

  ahbh.append((a.length() - ahalflen) + (b.length() - bhalflen), '0');
  ahbt.append(a.length() - ahalflen, '0');
  atbh.append(b.length() - bhalflen, '0');

  string res = "";
  res = add(ahbh, ahbt);
  res = add(res, atbh);
  res = add(res, atbt);

  return res;
}

int main() {
  string a, b;
  while (cin >> a >> b) {
    auto start = system_clock::now();
    cout << a << "*" << b << "=" << cal(a, b) << endl;
    duration<double> diff = system_clock::now() - start;
    cout << "用时 " << diff.count() * 1000 << " 毫秒" << endl;
  }
  return 0;
}