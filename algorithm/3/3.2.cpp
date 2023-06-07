#include <climits>
#include <iostream>
using namespace std;
#define MAX 1001

// 参考https://blog.csdn.net/qq_44755403/article/details/105015330

// 记录从i到j个矩阵的最小代价
int ans[MAX][MAX];
// 记录最小代价时分割点
int divide[MAX][MAX];

void MatrixChainOrder(int p[], int n) {
  for (int i = 1; i <= n; i++) {
    divide[i][i] = i;
  }
  for (int h = 2; h <= n; h++) {
    for (int i = 1; i <= n - h + 1; i++) {
      int j = i + h - 1;
      ans[i][j] = INT_MAX;
      for (int tmp, d = divide[i][j - 1]; d <= divide[i + 1][j]; d++) {
        tmp = ans[i][d] + ans[d + 1][j] + p[i - 1] * p[d] * p[j];

        if (tmp < ans[i][j]) {
          ans[i][j] = tmp;
          divide[i][j] = d;
        }
      }
    }
  }
}

void PrintDivide(int i, int j) {
  if (i == j) {
    cout << "A" << i;
  } else {
    int d = divide[i][j];
    cout << "(";
    PrintDivide(i, d);
    PrintDivide(d + 1, j);
    cout << ")";
  }
}

int main() {
  // n: 3
  // arr: 10 100 5 50
  // n: 6
  // arr: 30 35 15 5 10 20 25
  int n;
  cin >> n;
  int *arr = new int[n + 1];
  for (int i = 0; i < n + 1; i++) {
    cin >> arr[i];
  }
  MatrixChainOrder(arr, n);
  cout << "最优解：" << ans[1][n] << endl;
  if (n == 1) {
    cout << "(A1)" << endl;
  } else {
    PrintDivide(1, n);
    cout << endl;
  }
  delete[] arr;
}