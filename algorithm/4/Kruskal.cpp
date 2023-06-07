#include <algorithm>
#include <iostream>
#include <ostream>
#include <queue>
#include <sstream>
#include <vector>

using namespace std;

struct Edge {
  // u, v表示两个邻接的点，weight表示边的权重
  int u, v, weight;
  Edge(int u, int v, int weight) : u(u), v(v), weight(weight) {}
};

// 定义比较规则
struct Compare {
  bool operator()(Edge a, Edge b) { return a.weight > b.weight; }
};

vector<int> parent;  // 父节点

// 并查集算法，参考https://blog.csdn.net/bjweimengshu/article/details/108332389

// 查找给定元素所在集合的根节点，这里用于查找起点，确定分支
int find(int x) {
  if (parent[x] != x) {
    parent[x] = find(parent[x]);
  }
  return parent[x];
}

// 合并两个集合，使用根节点的父节点指向另一个根节点，也就是这里开始出现不同的分支
void unionSet(int x, int y) { parent[find(x)] = find(y); }

int kruskal(int n, vector<Edge> &edges) {
  parent.resize(n);
  for (int i = 0; i < n; i++) {
    parent[i] = i;
  }
  priority_queue<Edge, vector<Edge>, Compare> pq(edges.begin(), edges.end());
  int cost = 0;
  while (!pq.empty()) {
    Edge edge = pq.top();
    pq.pop();
    if (edge.weight == 0) {
      continue;  // 权重为0，不可达
    }
    int u = edge.u;
    int v = edge.v;
    if (find(u) != find(v)) {  // 判断u，v是否属于同一个分支
      unionSet(u, v);
      cout << u + 1 << "<-" << v + 1 << " 代价: " << edge.weight << endl;
      cost += edge.weight;
    }
  }
  return cost;
}

int main() {
  int n = 8;
  vector<vector<int>> graph(n, vector<int>(n));
  vector<Edge> edges;

  for (int i = 0; i < n; i++) {
    string line;
    getline(cin, line);
    istringstream iss(line);
    for (int j = 0; j < n; j++) {
      iss >> graph[i][j];
      edges.push_back({i, j, graph[i][j]});
    }
  }
  int cost = kruskal(n, edges);
  cout << "最小代价: " << cost << endl;
}