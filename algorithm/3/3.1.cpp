#include <iostream>
using namespace std;

// 参考https://blog.csdn.net/weixin_44023658/article/details/105965361

const int MaxVal = 99999;

const int n = 5;  // 5个节点
// 每个节点查找成功的概率
double p[n + 1] = {-1, 0.15, 0.10, 0.05, 0.10, 0.20};
// 除去每个节点的区间，查找失败的概率
double q[n + 1] = {0.05, 0.10, 0.05, 0.05, 0.05, 0.10};
// 根节点
int root[n + 1][n + 1];
// 若干节点的期望概率，二维下标表示区间
double e[n + 2][n + 2];
// 若干节点的概率总和，二维下标表示区间
double w[n + 2][n + 2];

void optimalBST(double *p, double *q, int n) {
  // 初始化虚拟节点
  for (int i = 1; i <= n + 1; i++) {
    w[i][i - 1] = q[i - 1];
    e[i][i - 1] = q[i - 1];
  }

  // 从下至上，从左往右计算
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n - i + 1; j++) {
      int t = j + i - 1;
      e[j][t] = MaxVal;
      w[j][t] = w[j][t - 1] + p[t] + q[t];
      // 寻找代价最小的子树的根
      for (int k = j; k <= t; k++) {
        double tmp = e[j][k - 1] + e[k + 1][t] + w[j][t];
        if (tmp < e[j][t]) {
          e[j][t] = tmp;
          root[j][t] = k;
        }
      }
    }
  }
}

// 打印一张二维表，记录各个子树最小代价时的根节点的序列值
// 左上为左子树，右上为根，右下为右子树
void printRoot() {
  cout << "各子树的根：" << endl;
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= n; j++) {
      cout << root[i][j] << " ";
    }
    cout << endl;
  }
  cout << endl;
}

void printTree(int i, int j, int r) {
  int rootChild = root[i][j];     // 从root表取出对应根节点的序列值
  if (rootChild == root[1][n]) {  // 整个树的根节点
    cout << "k" << rootChild << "是根" << endl;
    printTree(i, rootChild - 1, rootChild);
    printTree(rootChild + 1, j, rootChild);
    return;
  }
  if (j < i - 1) {
    return;
  } else if (j == i - 1) {  // 虚拟节点
    if (j < r) {  // 根据虚拟节点相对子树根节点的位置判断
      cout << "d" << j << "是k" << r << "的左孩子" << endl;
    } else {
      cout << "d" << j << "是k" << r << "的右孩子" << endl;
    }
    return;
  } else {  // 其余的内部成员节点
    // rootChild是本次的节点，也是下一次的父节点
    // r则是上一次的父节点，是上一次的rootChild
    // 那么这里的比较实际上就是子节点与父节点的位置
    if (rootChild < r) {
      cout << "k" << rootChild << "是k" << r << "的左孩子" << endl;
    } else {
      cout << "k" << rootChild << "是k" << r << "的右孩子" << endl;
    }
  }
  printTree(i, rootChild - 1, rootChild);
  printTree(rootChild + 1, j, rootChild);
}

int main() {
  for (int i = 0; i < n + 1; i++) {
    cin >> p[i];
  }
  for (int i = 0; i < n + 1; i++) {
    cin >> q[i];
  }
  optimalBST(p, q, n);
  printRoot();
  cout << "最优二叉树结构：" << endl;
  printTree(1, n, -1);
}