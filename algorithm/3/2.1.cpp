#include <chrono>
#include <fstream>
#include <iostream>
#include <string>
using namespace std;
using namespace chrono;

// 参考https://blog.csdn.net/hanmo22357/article/details/124355481

inline int max(const int& a, const int& b, const int& c) {
  if (a >= b && a >= c) {
    return a;
  } else if (b >= a && b >= c) {
    return b;
  } else {
    return c;
  }
}

// 三重循环
int BruteForce(const int* a, const int& n) {
  int max = 0;
  for (int length = 1; length <= n; length++) {  // 所有可能的子段长度
    for (int i = 0; i <= n - length; i++) {      // 子段起始下标遍历
      int sum = 0;
      for (int j = i; j < i + length; j++) {  // 根据假设的子段长度遍历累加
        sum += a[j];
      }
      if (sum > max) {
        max = sum;
      }
    }
  }
  return max;
}

// 分治法
int DivideConquer(const int* a, const int& left, const int& right) {
  if (right - left <= 1) {  // 左右相邻时，若左值大于零则返回左值，否则返回零
    if (a[left] > 0) {
      return a[left];
    } else {
      return 0;
    }
  }
  int middle = (left + right) / 2;  // 取中间下标值
  int leftMax = 0, rightMax = 0;    // 左右的最大值
  int leftSum = 0, rightSum = 0;    // 左右的累加值
  // 求出左边的最大值，需要注意这里是从右往左累加
  for (int i = middle - 1; i >= left; i--) {
    leftSum += a[i];
    if (leftSum >= leftMax) {
      leftMax = leftSum;
    }
  }
  // 求出右边的最大值
  for (int i = middle; i < right; i++) {
    rightSum += a[i];
    if (rightSum >= rightMax) {
      rightMax = rightSum;
    }
  }
  // 返回最大值，第一个参数是左半部分的最大值，第二参数是右半部分的最大值，第三个参数是综合左右部分的最大值
  return max(DivideConquer(a, left, middle), DivideConquer(a, middle, right),
             leftMax + rightMax);
}

// 动态规划法
int DynamicProgram(int* a, const int& n) {
  int* temp = new int[n];
  temp[0] = a[0] > 0 ? a[0] : 0;  // 起始值初始化
  for (int i = 1; i < n; i++) {
    temp[i] = temp[i - 1] > 0
                  ? (temp[i - 1] + a[i])
                  : a[i];  // 上一个值大于零，则累加，否则初始化为当前值
  }
  // 遍历完后，得到各位上以该位作为结尾的最大值，从这些最大值中再找出最大值，即为最终结果
  int max = 0;
  for (int i = 0; i < n; i++) {
    if (temp[i] > max) {
      max = temp[i];
    }
  }
  return max;
}

int main() {
  //   int a[] = {-2, 11, -4, 13, -5, -2};
  int a[6];
  for (int i = 0; i < 6; i++) {
    cin >> a[i];
  }

  for (int i = 0; i < 6; i++) {
    cout << a[i] << " ";
  }
  cout << endl;
  auto start = system_clock::now();
  duration<double> diff;
  int res;

  start = system_clock::now();
  res = BruteForce(a, 6);
  diff = system_clock::now() - start;
  cout << "三重循环结果: " << res << ", 用时" << diff.count() * 1000 << "毫秒"
       << endl;

  start = system_clock::now();
  res = DivideConquer(a, 0, 6);
  diff = system_clock::now() - start;
  cout << "分治法结果: " << res << ", 用时" << diff.count() * 1000 << "毫秒"
       << endl;

  start = system_clock::now();
  res = DynamicProgram(a, 6);
  diff = system_clock::now() - start;
  cout << "动态规划法结果: " << res << ", 用时" << diff.count() * 1000 << "毫秒"
       << endl;
}
