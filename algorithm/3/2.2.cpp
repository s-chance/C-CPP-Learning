#include <chrono>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <vector>
using namespace std;
using namespace chrono;

double BruteForce(double *a, int n, int &besti, int &bestj) {
  double max = 0;
  for (int i = 0; i <= n; i++) {    // 起始下标
    for (int j = i; j <= n; j++) {  // 可能的长度
      double sum = 0;
      for (int k = i; k <= j; j++) {  // 指定长度区间累加
        sum += a[i];
      }
      if (sum > max) {
        max = sum;
        besti = i;  // 起始位置
        bestj = j;  // 结束位置
      }
    }
  }
  return max;
}

double DivideConquer(double *a, int left, int right) {
  double max = 0;
  if (left == right) {
    max = a[left] > 0 ? a[left] : 0;
  } else {
    int middle = (left + right) / 2;
    double leftMax = DivideConquer(a, left, middle);
    double rightMax = DivideConquer(a, middle + 1, right);
    double leftSum = 0, leftTmp = 0;
    double rightSum = 0, rightTmp = 0;
    for (int i = middle - 1; i >= left; i--) {
      leftSum += a[i];
      if (leftSum > leftTmp) {
        leftTmp = leftSum;
      }
    }
    for (int i = middle; i < right; i++) {
      rightSum += a[i];
      if (rightSum > rightTmp) {
        rightTmp = rightSum;
      }
    }
    max = leftTmp + rightTmp;
    if (max < leftMax) {
      max = leftMax;
    }
    if (max < rightMax) {
      max = rightMax;
    }
  }
  return max;
}

double DynamicProgram(double *a, int n, int &besti, int &bestj) {
  double max = 0, tmp = 0;
  tmp = a[0] > 0 ? a[0] : 0;
  for (int i = 1; i <= n; i++) {
    if (tmp > 0) {
      tmp += a[i];
    } else {
      tmp = a[i];
      besti = i;
    }
    if (tmp > max) {
      max = tmp;
      bestj = i;
    }
  }
  return max;
}

int main() {
  ifstream infile;
  infile.open(
      "/home/entropy/Documents/CPP-Practice/algorithm/3/"
      "太阳黑子处理后数据.txt");
  if (!infile.is_open()) {
    cout << "文件打开失败！" << endl;
    return -1;
  }
  vector<string> vec;
  string tmp;
  getline(infile, tmp);  // 提前读取行首非数据部分
  while (getline(infile, tmp)) {
    vec.push_back(tmp);
  }
  double a[500] = {0};
  int j = 0;
  for (auto i = vec.begin(); i != vec.end(); i++) {
    stringstream ss(*i);
    string s;
    int tmp = 0;
    while (ss >> s) {
      if (tmp == 2) {
        double r = atof(s.c_str());
        a[j] = r;
        j++;
      }
      tmp++;
    }
  }
  int besti, bestj;
  double res;

  auto start = system_clock::now();
  duration<double> diff;

//   start = system_clock::now();
//   res = BruteForce(a, j, besti, bestj);
//   diff = system_clock::now() - start;
//   cout << "三重循环结果: " << res << ", 用时" << diff.count() * 1000 << "毫秒"
//        << endl;
  start = system_clock::now();
  res = DivideConquer(a, 0, j);
  diff = system_clock::now() - start;
  cout << "分治法结果: " << res << ", 用时" << diff.count() * 1000 << "毫秒"
       << endl;

  start = system_clock::now();
  res = DynamicProgram(a, j,besti,bestj);
  diff = system_clock::now() - start;
  cout << "动态规划法结果: " << res << ", 用时" << diff.count() * 1000 << "毫秒"
       << endl;

  cout << "太阳黑子最大爆发年份：";
  cout << vec.at(bestj) << endl;

  infile.close();
}