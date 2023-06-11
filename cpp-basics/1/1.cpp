#include <cstdlib>
#include <ctime>
#include <iostream>
using namespace std;

int *InitArray(unsigned n) {
  unsigned seed = time(0);  // 随机数生成
  srand(seed);
  int *p = new int[n];  // 手动分配内存
  for (int i = 0; i < n; i++) {
    p[i] = rand() % 10000;  // 这里取四位数，方便观察
  }
  return p;
}

void Display(int *p, int n) {
  for (int i = 0; i < n; i++) {
    cout << *p << " ";
    p++;
  }
  cout << endl;
}

void quickSort(int *p, int *newArray, int left, int right) {
  if (left >= right) {  // 快排退出条件
    return;
  }

  int first = left, last = right;
  int x = newArray[first];  // 基准值
  int xx = p[first];
  while (left < right) {
    while (newArray[right] >= x && left < right) {
      right--;
    }
    while (newArray[left] <= x && left < right) {
      left++;
    }
    if (left < right) {
      swap(newArray[left], newArray[right]);
      swap(p[left], p[right]);
    }
  }
  swap(newArray[first], newArray[left]);
  swap(p[first], p[left]);
  quickSort(p, newArray, first, left - 1);
  quickSort(p, newArray, left + 1, last);
}

void SortArray(int *p, int n) {
  int *newArray = new int[n];
  for (int i = 0; i < n; i++) {
    int newNum = 0, origin = p[i] % 1000;  // 按个、十、百依次取位，计算新数值
    while (origin) {
      int a = origin % 10;
      newNum = newNum * 10 + a;
      origin /= 10;
    }
    if (p[i] % 1000 < 100 && p[i] % 1000 > 9) {
      newNum *= 10;  // 只占二位不足三位的补位
    }
    if (p[i] % 1000 < 10) {
      newNum *= 100;  // 只有个位数的补到三位
    }
    newArray[i] = newNum;  // 得到新数值的数组
  }

  // 快速排序处理较大规模数据
  quickSort(p, newArray, 0, n - 1);
}

void DestroyArray(int *p) {
  delete[] p;  // 释放内存
}

int main() {
  unsigned n;
  int *p;
  while (cin >> n) {
    p = InitArray(n);
    // 初始化一个规模为n的一维整型数组，并给出随机互异的值进行初始化
    Display(p, n);  // 显示数据的初始化情况
    SortArray(p, n);
    // 根据每个数包含的数字按个位、十位和百位和组成的新数值进行升序整理；如123对应的新数值为321，12的对应的新数值为210
    Display(p, n);    // 显示排序后的结果
    DestroyArray(p);  // 根据需要使用
  }
  return 0;
}