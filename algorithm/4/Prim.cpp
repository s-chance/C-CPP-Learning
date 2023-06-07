#include <cstdio>
#include <iostream>
#include <sstream>
using namespace std;

void Prim(int n, int **c) {
  int lowcost[n];  // 最短边长度
  int closest[n];  // 邻接点
  bool s[n];       // 是否已经经过i顶点
  s[0] = true;     // 起点
  // 初始化
  for (int i = 0; i < n; i++) {
    lowcost[i] = c[0][i];  // 从点1到其他所有点的距离，0表示自身或没有边相连
    closest[i] = 1;  // 初始化其他所有点的邻接点为1
    s[i] = false;    // 初始化其他所有点为未经过状态
  }

  int cost = 0;  // 最小代价

  for (int i = 1; i < n; i++) {
    int min = 32767;  // 寻找最短边长度
    int j = 0;        // j表示当前点的下标
    // 找到最短边所对应的下一个点
    for (int k = 1; k < n; k++) {  // k从1开始，因为k=0已经在前面初始化完成
      if (lowcost[k] == 0) {
        continue;  // 排除距离为0的下一个点
      }
      if (lowcost[k] < min && !s[k]) {
        min = lowcost[k];
        j = k;  // j赋值为下一个点的下标
      }
    }
    // 输出格式: 下一个点 上一个点
    // 两点之间的边满足最短边长度
    cout << j + 1 << "<-" << closest[j] << " 代价: " << lowcost[j] << endl;
    s[j] = true;  // 该点已被使用
    cost += lowcost[j];
    // 以当前点为起点更新其lowcost和closest
    for (int k = 1; k < n; k++) {
      if (c[j][k] == 0) {
        continue;  // 排除距离为0的下一个点
      }
      // 距离为0，则一定是未经过的状态
      if ((c[j][k] < lowcost[k] || lowcost[k] == 0) && !s[k]) {
        lowcost[k] = c[j][k];
        closest[k] = j + 1;
      }
    }
  }
  cout << "最小代价: " << cost << endl;
}
int main() {
  const int n = 8;
  int **c = new int *[n];
  for (int i = 0; i < n; i++) {
    c[i] = new int[n];
  }
  for (int i = 0; i < n; i++) {
    string line;
    getline(cin, line);
    istringstream iss(line);
    for (int j = 0; j < n; j++) {
      iss >> c[i][j];  // c[i][j]表示从i点到j点的距离
    }
  }

  Prim(n, c);

  for (int i = 0; i < n; i++) {
    delete[] c[i];
  }
  delete[] c;
}