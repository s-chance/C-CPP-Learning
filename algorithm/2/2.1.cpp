#include <algorithm>
#include <chrono>
#include <iostream>
using namespace std;
using namespace chrono;

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

// a：无序数列
// len：数列长度
// n：递归次数，第i次递归找到第i+1大的值
int search(int *a, int len, int n) {
  int *max = &a[0];
  int pos = 0;  // 记录最大值下标

  // 寻找最大值
  for (int i = 1; i < len; i++) {
    if (*max < a[i]) {
      max = &a[i];
      pos = i;
    }
  }

  // 返回第n+1大的值
  if (n == 0) {
    return *max;
  }

  // 创建排除了最大值的新数组
  int ans[len - 1];
  int k = 0;
  for (int j = 0; j < len; j++) {
    if (j == pos) {
      continue;
    }
    ans[k] = a[j];
    k++;
  }

  return search(ans, len - 1, n - 1);
}

// a：无序数列
// len：数列长度
// n：第n+1大的值
int countSort(int *a, int len, int n) {
  int *max = &a[0];
  int *min = &a[0];
  // 找到最大值和最小值
  for (int i = 1; i < len; i++) {
    if (*max < a[i]) {
      max = &a[i];
    }
    if (*min > a[i]) {
      min = &a[i];
    }
  }

  // 统计
  int length = *max - *min + 1;  // 计数器数组长度
  int *counter = new int[length]();
  for (int j = 0; j < len; j++) {
    counter[a[j] - *min]++;
  }

  int ans[len];

  // 排序
  int j = 0;
  for (int k = 0; k < length;) {  // 遍历计数器
    if (counter[k] == 0) {
      k++;  // 下一个计数器
      continue;
    }
    ans[j] = *min + k;  // 实际值为最小值+计数器的下标
    j++;
    counter[k]--;
  }
  return ans[len - 1 - n];
}

int main() {
  //   int a[7] = {4, 59, 7, 23, 61, 55, 46};
  int a[7];
  for (int i = 0; i < 7; i++) {
    cin >> a[i];
  }
  int len = sizeof(a) / sizeof(int);
  int copyArr[len];  // 数组副本
  double avg = 0;    // 平均用时

  //   cout << "最大值： " << search(a, len, 0) << endl;
  //   cout << "第二大值： " << search(a, len, 1) << endl;
  //   cout << "第四大值： " << search(a, len, 3) << endl;

  //   copy(a, a + len, copyArr);
  //   cout << "最大值： " << randomizeSelect(copyArr, 0, len - 1, len) << endl;

  //   copy(a, a + len, copyArr);
  //   cout << "第二大值： " << randomizeSelect(copyArr, 0, len - 1, len - 1)
  //        << endl;

  //   copy(a, a + len, copyArr);
  //   cout << "第四大值： " << randomizeSelect(copyArr, 0, len - 1, len - 3)
  //        << endl;

  //   copy(a, a + len, copyArr);
  //   cout << "最大值： " << countSort(copyArr, len, 0) << endl;
  //   copy(a, a + len, copyArr);
  //   cout << "第二大值： " << countSort(copyArr, len, 1) << endl;
  //   copy(a, a + len, copyArr);
  //   cout << "第四大值： " << countSort(copyArr, len, 3) << endl;

  auto start = system_clock::now();
  duration<double> diff = system_clock::now() - start;
  int times = 1000000;  // 循环次数

  cout << "不使用排序算法" << endl;
  for (int i = 0; i < times; i++) {
    // 拷贝数组保证初始条件一致
    copy(a, a + len, copyArr);
    start = system_clock::now();
    randomizeSelect(copyArr, 0, len - 1, i % (len + 1));
    // cout << "最大值： " << randomizeSelect(copyArr, 0, len - 1, len) << endl;
    diff = system_clock::now() - start;
    avg += diff.count() * 1000;
    // cout << "用时： " << diff.count() * 1000 << " 毫秒" << endl;
  }
  cout << "平均用时: " << avg / times << " 毫秒" << endl;

  avg = 0;  // 平均用时初始化
  cout << "使用计数排序" << endl;
  for (int i = 0; i < times; i++) {
    copy(a, a + len, copyArr);

    start = system_clock::now();
    countSort(a, len, i % len);
    // cout << "最大值： " << countSort(copyArr, len, 0) << endl;
    diff = system_clock::now() - start;
    avg += diff.count() * 1000;
    // cout << "用时： " << diff.count() * 1000 << " 毫秒" << endl;
  }
  cout << "平均用时: " << avg / times << " 毫秒" << endl;
}
