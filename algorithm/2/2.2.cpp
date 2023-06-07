#include <algorithm>
#include <chrono>
#include <iostream>
using namespace std;
using namespace chrono;

void quickSort(int *arr, int left, int right) {
  if (left >= right) {
    return;
  }

  int first = left, last = right;
  int pivlot = arr[first];
  while (left < right) {
    while (arr[right] >= pivlot && left < right) {
      right--;
    }
    while (arr[left] <= pivlot && left < right) {
      left++;
    }
    if (left < right) {
      swap(arr[left], arr[right]);
    }
  }
  swap(arr[first], arr[left]);
  quickSort(arr, first, left - 1);
  quickSort(arr, left + 1, last);
}

int partition(int a[], int p, int r) {
  int i = p, j = r + 1;
  int x = a[p];
  while (true) {
    while (a[--j] >= x && j > p)
      ;
    while (a[++i] < x)
      ;

    if (i >= j) {
      break;
    }
    swap(a[i], a[j]);
  }
  a[p] = a[j];
  a[j] = x;
  return j;
}

int randomizePartition(int a[], int p, int r) {
  // 随机选择[p,r)区间的一个值作为基准
  srand((unsigned)time(0));
  int i = rand() % (r - p) + p;  // 获取下标

  // 调整基准值的位置
  swap(a[i], a[p]);

  return partition(a, p, r);
}

int randomizeSelect(int a[], int p, int r, int k) {
  if (p == r) {
    return a[p];
  }
  int i = randomizePartition(a, p, r);
  int j = i - p + 1;
  if (k <= j) {
    return randomizeSelect(a, p, i, k);
  } else {
    return randomizeSelect(a, i + 1, r, k - j);
  }
}

int main() {
  unsigned seed = time(0);
  srand(seed);

  //   int len = 10000;
  int len;
  cin >> len;

  int arr[len];
  int copyArr[len];

  for (int i = 0; i < len; i++) {
    arr[i] = rand() % 10000;
  }

  // 数组副本保证排序初始条件一致
  copy(arr, arr + len, copyArr);

  auto start = system_clock::now();
  duration<double> diff = system_clock::now() - start;

  cout << "randomizeSelect" << endl;
  start = system_clock::now();
  int value = randomizeSelect(arr, 0, len - 1, 4999);
  diff = system_clock::now() - start;
  cout << "第4999小的数: " << value << endl;
  cout << "用时: " << diff.count() * 1000 << " 毫秒" << endl;

  cout << "quickSort" << endl;
  start = system_clock::now();
  quickSort(copyArr, 0, len - 1);
  diff = system_clock::now() - start;
  cout << "第4999小的数: " << arr[4998] << endl;
  cout << "用时: " << diff.count() * 1000 << " 毫秒" << endl;
}