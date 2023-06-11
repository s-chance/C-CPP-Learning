#include <iomanip>
#include <iostream>
using namespace std;

void Display(int *, int, int);

void InitMatrix(int *arr, int n, int k) {
  for (int i = 0; i < n; i++) {
    for (int j = 0; j < k; j++) {
      // arr[i * k + j] = i * k + j + 1;
      cin >> arr[i * k + j];
    }
  }
  Display(arr, n, k);
}

int *Multiply(int *a, int *b, int n, int k, int m) {
  int *res = new int[n * m]();
  int p = 0;
  for (int h = 0; h < n; h++) {
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < k; j++) {
        res[h * m + i] += a[h * k + j] * b[j * m + i];
      }
    }
  }
  return res;
}

void Display(int *c, int row, int col) {
  for (int i = 0; i < row; i++) {
    for (int j = 0; j < col; j++) {
      cout << setw(3) << c[i * col + j] << " ";
    }
    cout << endl;
  }
}

int main() {
  const int n = 2;
  const int k = 3;
  const int m = 4;
  int a[n][k], b[k][m];
  int *c;

  InitMatrix(a[0], n, k);  // 初始化矩阵A
  InitMatrix(b[0], k, m);  // 初始化矩阵B

  c = Multiply(a[0], b[0], n, k, m);  // 计算 a X b

  Display(c, n, m);  // 输出计算结果
  return 0;
}