#include <climits>
#include <cstdio>
#include <iostream>
#include <queue>
#include <sstream>
#include <vector>
using namespace std;

const int n = 4;         // 城市数量
int graph[n][n];         // 邻接矩阵
bool visited[n];         // 是否经过
vector<int> path;        // 当前搜索路径
int min_cost = INT_MAX;  // 最小花费
vector<int> best_path;   // 当前最优路径

// 回溯法
void backtrack(int curr_cost) {
  if (path.size() == n) {
    if (curr_cost + graph[path.back()][0] < min_cost) {
      min_cost = curr_cost + graph[path.back()][0];
      best_path = path;
    }
    return;
  }
  for (int i = 0; i < n; i++) {
    if (!visited[i]) {
      visited[i] = true;
      path.push_back(i);
      backtrack(curr_cost + graph[path[path.size() - 2]][i]);
      path.pop_back();
      visited[i] = false;
    }
  }
}

// 分支界限法
struct Node {
  int level;
  int cost;
  int bound;
  vector<int> path;
};

struct cmp {
  bool operator()(Node& a, Node& b) { return a.bound > b.bound; }
};

// 计算bound值，由于邻接矩阵存在0值，这里需要做额外处理
int bound(Node& node) {
  int res = node.cost;
  for (int i = 0; i < n; i++) {
    if (!visited[i]) {
      int min1 = INT_MAX, min2 = INT_MAX;
      for (int j = 0; j < n; j++) {
        if (i != j && graph[i][j] < min1 && graph[i][j]) {
          min2 = min1;
          min1 = graph[i][j];
        } else if (i != j && graph[i][j] < min2 && graph[i][j]) {
          min2 = graph[i][j];
        }
      }
      res += min1 + min2;
    }
  }
  return res / 2;
}

void backtrack2() {
  priority_queue<Node, vector<Node>, cmp> pq;
  Node root;
  root.level = 0;
  root.cost = 0;
  root.path.push_back(0);
  root.bound = bound(root);
  pq.push(root);

  while (!pq.empty()) {
    Node node = pq.top();
    pq.pop();
    if (node.bound < min_cost) {
      int level = node.level + 1;

      for (int i = 1; i < n; i++) {
        for (int p : node.path) {
          // 由于visited用于处理bound函数之后被重置，
          // 这里需要重新更新visited的状态
          if (p == i) {
            visited[i] = true;
          }
        }
        if (!visited[i] && graph[node.path.back()][i]) {  // 未拜访的地点
          Node child = node;
          child.level = level;
          child.cost += graph[child.path.back()][i];
          child.path.push_back(i);
          if (level == n - 1) {  // 到达最后一个城市，回到起点
            child.cost += graph[child.path.back()][0];
            if (child.cost < min_cost) {
              min_cost = child.cost;
              best_path = child.path;
            }
          } else {
            visited[i] = true;  // 这里用visited防止当前城市bound值被覆盖
            // 在假设当前城市已被访问的情况下计算子节点bound
            child.bound = bound(child);
            if (child.bound < min_cost) {
              pq.push(child);
            }
            visited[i] = false;  // 这里重新将visited复原
            // 实际上这里的访问只是一种可能性，而不是真正的访问
          }
        }
      }
    }
  }
}

int main() {
  for (int i = 0; i < n; i++) {
    string line;
    getline(cin, line);
    istringstream iss(line);
    for (int j = 0; j < n; j++) {
      iss >> graph[i][j];
    }
  }

  path.push_back(0);
  visited[0] = true;
//   backtrack(0);
    backtrack2();
  cout << "最小花费: " << min_cost << endl;

  cout << "最优路径: ";
  for (int i = 0; i < best_path.size(); i++) {
    cout << best_path[i] << " ";
  }
  cout << endl;
}