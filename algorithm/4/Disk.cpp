#include <algorithm>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <ostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

// 参考: https://blog.csdn.net/lfb637/article/details/80550601

// 径向距离
int d(int i, int j) { return abs(i - j); }

// 期望时间
double cost(double pi, double pj, int d) { return (pi * pj * d); }

// 自定义sort函数降序排序
bool cmp(double a, double b) { return a > b; }

// 排序: 中间大，两边小
void strageSort(int n, double *a) {
  int i, j, mid;
  sort(a, a + n, cmp);
  mid = n / 2;
  double b[n];
  b[mid] = a[0];
  for (int i = 1, j = 1; i < n; i++, j++) {
    b[mid - j] = a[i];
    i++;
    if (i != n) {
      b[mid + j] = a[i];
    }
  }
  for (int i = 0; i < n; i++) {
    a[i] = b[i];
  }
}

double minStorage(int n, double *a) {
  double res = 0;
  for (int i = 0; i < n; i++) {
    for (int j = i + 1; j < n; j++) {
      res += cost(a[i], a[j], d(i, j));
    }
  }
  return res;
}

int main() {
  ifstream input;
  input.open("/home/entropy/Documents/CPP-Practice/algorithm/4/input.txt");
  if (!input.is_open()) {
    cout << "文件打开失败! " << endl;
    return -1;
  }
  int n;
  input >> n;
  double a[n];
  double sum = 0;  // 总概率
  for (int i = 0; i < n; i++) {
    input >> a[i];
    sum += a[i];
  }
  for (int i = 0; i < n; i++) {
    a[i] /= sum;  // 实际概率
  }

  strageSort(n, a);
  double cost = minStorage(n, a);
  cout << "最小期望检索时间: " << cost << endl;
  ofstream output;
  output.open("/home/entropy/Documents/CPP-Practice/algorithm/4/output.txt");
  if (!output.is_open()) {
    cout << "文件打开失败! " << endl;
    return -1;
  }
  output << cost;
}