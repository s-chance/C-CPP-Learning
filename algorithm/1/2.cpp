#include <chrono>
#include <iostream>
#include <type_traits>
using namespace std;
using namespace chrono;

// // 最大堆化(非递归实现)
// void heapify(int* arr, int head, int tail) {
//   int parent = head;           // 父节点
//   int child = parent * 2 + 1;  // 父节点的左子节点
//   while (child <= tail) {

//     // 比较左右子节点的大小，选择最大的子节点
//     if (child + 1 <= tail && arr[child] < arr[child + 1]) {
//       child++;
//     }
//     if (arr[parent] > arr[child]) {
//       return;
//     } else {
//       swap(arr[parent], arr[child]);
//         parent = child;
//         child = parent * 2 + 1;
//     }
//   }
// }

// 最大堆化(递归实现)
void heapify(int* arr, int head, int tail) {
  if (head > tail) {
    return;
  }
  int parent = head;            // 父节点
  int lchild = parent * 2 + 1;  // 父节点的左子节点
  int rchild = parent * 2 + 2;  // 父节点的右子节点

  if (lchild <= tail && arr[lchild] > arr[parent]) {
    parent = lchild;
  }
  if (rchild <= tail && arr[rchild] > arr[parent]) {
    parent = rchild;
  }

  if (parent != head) {
    swap(arr[parent], arr[head]);
    heapify(arr, parent, tail);
  }
}

void heapSort(int* arr, int len) {
  for (int i = len / 2 - 1; i >= 0; i--) {
    heapify(arr, i, len - 1);
  }
  for (int i = len - 1; i > 0; i--) {
    swap(arr[0], arr[i]);
    heapify(arr, 0, i - 1);
  }
}
void quickSort(int* arr, int first, int last) {
  if (first >= last) {
    return;
  }

  int left = first, right = last;
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

void testHeapSort(int* arr, int len) { heapSort(arr, len); }

void testQuickSort(int* arr, int n) { quickSort(arr, 0, n - 1); }

int main() {
  cout << "输入数列的长度: ";
  int n;
  cin >> n;
  srand(time(0));
  int* arr = new int[n]();
  for (int i = 0; i < n; i++) {
    arr[i] = rand();
  }

  // 拷贝一份数据，保证两种方法测试的初始数据一致
  int* copyArr = new int[n];
  for (int i = 0; i < n; i++) {
    copyArr[i] = arr[i];
  }

  cout << "堆排序: ";
  auto start = system_clock::now();
  testHeapSort(arr, n);
  duration<double> diff = system_clock::now() - start;
  cout << "用时 " << diff.count() * 1000 << " 毫秒" << endl;

  //   for (int i = 0; i < n; i++) {
  //     cout << arr[i] << " ";
  //   }
  //   cout << endl;

  cout << "快速排序: ";
  start = system_clock::now();
  testQuickSort(copyArr, n);
  diff = system_clock::now() - start;
  cout << "用时 " << diff.count() * 1000 << " 毫秒" << endl;

  //   for (int i = 0; i < n; i++) {
  //     cout << copy[i] << " ";
  //   }
  //   cout << endl;
  delete[] arr;
  delete[] copyArr;
  return 0;
}