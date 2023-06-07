#include <algorithm>
#include <cstdio>
#include <iostream>
#include <string>
using namespace std;

// 输出公共子序列
void LCS(int i, int j, char *x, int **c) {
  if (i == 0 || j == 0) {
    return;
  }
  if (c[i][j] == c[i - 1][j - 1] + 1) {
    LCS(i - 1, j - 1, x, c);
    cout << x[i - 1];
  } else if (c[i][j] == c[i - 1][j]) {
    LCS(i - 1, j, x, c);
  } else {
    LCS(i, j - 1, x, c);
  }
}

// 统计公共子序列长度
void LCSLength(int m, int n, char *x, char *y, int **c) {
  int i, j;
  for (i = 1; i <= m; i++) {
    for (j = 1; j <= n; j++) {
      if (x[i - 1] == y[j - 1]) {
        c[i][j] = c[i - 1][j - 1] + 1;
      } else if (c[i - 1][j] > c[i][j - 1]) {
        c[i][j] = c[i - 1][j];
      } else {
        c[i][j] = c[i][j - 1];
      }
    }
  }
  cout << c[m][n] << endl;
  LCS(m, n, x, c);
}

int main() {
  // X: ABCBDAB
  // Y: BDCABA
  // X: zhejiang university of technology
  // Y: zhejiang university city college
  string X, Y;
  getline(cin, X);
  getline(cin, Y);
  int m = X.length();
  int n = Y.length();
  int **c = new int *[m + 1]();
  for (int i = 0; i <= m; i++) {
    c[i] = new int[n + 1]();
  }
  LCSLength(m, n, &X[0], &Y[0], c);
}