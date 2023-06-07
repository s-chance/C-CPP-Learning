#include <algorithm>
#include <iostream>
#include <queue>
#include <vector>
using namespace std;

// 回溯法
void dfs(vector<char> &vec, int start, vector<vector<char>> &res) {
  if (start == vec.size()) {
    res.push_back(vec);
    return;
  }
  // 全排列实现
  for (int i = start; i < vec.size(); i++) {
    swap(vec[start], vec[i]);
    dfs(vec, start + 1, res);
    swap(vec[start], vec[i]);
  }
}

vector<vector<char>> func_dfs(vector<char> &vec) {
  vector<vector<char>> res;
  dfs(vec, 0, res);
  return res;
}

// 分支界限法
struct Node {
  int level;
  vector<char> ans;
};

vector<vector<char>> func_bfs(vector<char> &vec) {
  vector<vector<char>> res;
  queue<Node> q;
  Node root = {0, {}};
  q.push(root);
  while (!q.empty()) {
    Node node = q.front();  // 获取前缀
    q.pop();
    if (node.level == vec.size()) {
      res.push_back(node.ans);  // 存储结果
      continue;
    }
    for (char ch : vec) {
      // 找到ans中不存在的字符
      if (find(node.ans.begin(), node.ans.end(), ch) == node.ans.end()) {
        Node newNode = node;
        newNode.ans.push_back(ch);
        newNode.level++;
        q.push(newNode);  // q存储了char数据
      }
    }
  }
  return res;
}

int main() {
  int n;
  cin >> n;
  char *ch = new char[n];
  vector<char> vec;
  for (int i = 0; i < n; i++) {
    cin >> ch[i];
    vec.push_back(ch[i]);
  }

  int ans = 0;
  //   vector<vector<char>> res = func_dfs(vec);
  vector<vector<char>> res = func_bfs(vec);
  for (auto &vec : res) {
    for (char ch : vec) {
      cout << ch << " ";
    }
    ans++;
    cout << endl;
  }
  cout << "全排列有: " << ans << "种" << endl;
  delete[] ch;
}