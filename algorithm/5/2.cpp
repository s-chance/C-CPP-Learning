#include <bits/types/FILE.h>

#include <iostream>
#include <queue>
#include <stack>
#include <vector>
using namespace std;

// 参考: https://blog.csdn.net/m0_57736712/article/details/124723032

//  动态规划
int V[1000][1000];
bool x[1000];  // 表示第i个物品是否放入背包
void dp(int n, int c, int *v, int *w) {
  for (int i = 1; i <= n; i++) {
    for (int j = 1; j <= c; j++) {
      if (j < w[i]) {
        V[i][j] = V[i - 1][j];
      } else {
        V[i][j] = max(V[i - 1][j], (V[i - 1][j - w[i]] + v[i]));
      }
    }
  }

  // 根据V的关系，判断哪些物品放入了背包
  int j = c;
  for (int i = n; i >= 1; i--) {
    if (V[i][j] == V[i - 1][j]) {
      x[i] = false;
    } else {
      x[i] = true;
      j -= w[i];
    }
  }

  cout << "放入背包的物品: ";
  for (int i = 1; i <= n; i++) {
    if (x[i]) {
      cout << i << " ";
    }
  }
  cout << endl;
  cout << "最优解: " << V[n][c] << endl;
}

// 参考: https://blog.csdn.net/hanmo22357/article/details/124371395
//  回溯法
bool xx[1000];  // 第i个物品是否放入背包
void funcDfs(int n, int c, int *v, int *w) {
  stack<int> bag;  // 背包
  int max = 0;     // 最大价值
  int weight = 0;  // 当前物品总重量
  int value = 0;   // 当前物品总价值

  for (int i = 1;; i++) {
    if (weight + w[i] <= c) {
      // 不会超重，则放入背包
      bag.push(i);
      weight += w[i];
      value += v[i];
      x[i] = true;
    }  // 超重的情况不做任何处理

    if (i == n) {  // 遍历到了最后一个物品，比较当前总价值
      if (max < value) {
        max = value;
        for (int i = 1; i <= n; i++) {
          xx[i] = x[i];
        }
      }

      // 取出装入背包的最后一件物品
      i = bag.top();
      bag.pop();
      weight -= w[i];
      value -= v[i];
      x[i] = false;
      if (i == n) {
        // 最后装入背包的物品本来就是编号最大的物品
        // 额外进行一次回溯
        if (bag.empty()) {
          break;
        }
        i = bag.top();
        bag.pop();
        weight -= w[i];
        value -= v[i];
        x[i] = false;
      }
    }
  }
  cout << "放入背包的物品: ";
  for (int i = 1; i <= n; i++) {
    if (xx[i]) {
      cout << i << " ";
    }
  }
  cout << endl;
  cout << "最优解: " << max << endl;
}

// 分支界限法
// 节点
struct Node {
  int level;
  int currV;
  int currW;
  double bound;
};

// 计算当前节点的最大上界
double bound(int n, int c, int *v, int *w, Node node) {
  int j, k;
  int weight;
  double res;
  if (node.currW >= c) {
    return 0;  // 当前节点超重
  } else {
    res = node.currV;
    weight = node.currW;
    j = node.level + 1;  // 子节点
    while (j <= n && (weight + w[j] <= c)) {
      weight += w[j];
      res += v[j];
      j++;
    }
    k = j;
    if (k <= n) {  // 若还有剩余物品，计算其单位价值
      res += v[k] * (c - weight) * 1.0 / w[k];
    }
    return res;
  }
}

struct cmp {
  bool operator()(Node a, Node b) { return a.bound < b.bound; }
};

bool yy[1000];  // 第i个物品是否放入背包
void funcBfs(int n, int c, int *v, int *w) {
  priority_queue<Node, vector<Node>, cmp> pq;
  Node a, b;
  a.level = 0;
  a.currV = 0;
  a.currW = 0;
  a.bound = bound(n, c, v, w, a);
  pq.push(a);

  int max = 0;
  while (!pq.empty()) {
    a = pq.top();
    pq.pop();

    if (a.bound > max) {
      b.level = a.level + 1;
      b.currV = a.currV + v[b.level];
      b.currW = a.currW + w[b.level];

      if (b.currW <= c && b.currV > max) {
        max = b.currV;
        x[b.level] = true;
        for (int i = b.level; i <= n; i++) {
          yy[i] = x[i];
        }
        int sum = 0;
        for (int i = 1; i <= n; i++) {
          if (yy[i]) {
            sum += v[i];
          }
          if (sum > max) {
            int flag = b.level - 1;
            while (!yy[flag]) {
              flag--;
            }
            yy[flag] = false; //更新物品存放状态
          }
        }
      }
      b.bound = bound(n, c, v, w, b);
      if (b.bound > max) {
        pq.push(b);  // 左子节点
      }
      x[b.level] = false;
      b.currV = a.currV;
      b.currW = a.currW;
      b.bound = bound(n, c, v, w, b);
      if (b.bound > max) {
        pq.push(b);  // 右子节点
      }
    }
  }

  cout << "放入背包的物品: ";
  for (int i = 1; i <= n; i++) {
    if (yy[i]) {
      cout << i << " ";
    }
  }
  cout << endl;
  cout << "最优解: " << max << endl;
}

int main() {
  int n;                    // 物品个数
  int c;                    // 背包容量
  cin >> n >> c;            // 5 10
  int *v = new int[n + 1];  // 物品体积
  int *w = new int[n + 1];  // 物品价值

  for (int i = 1; i <= n; i++) {
    cin >> v[i] >> w[i];
  }
  // dp(n, c, v, w);
  // funcDfs(n, c, v, w);
  funcBfs(n, c, v, w);
}