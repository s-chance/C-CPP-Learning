#include <cmath>
#include <iostream>
#include <queue>
#include <string>
#include <unordered_map>
#include <vector>
using namespace std;

// 节点定义
struct Node {
  char ch;
  int freq;
  Node *left, *right;
  Node(char ch, int freq, Node *left = nullptr, Node *right = nullptr)
      : ch(ch), freq(freq), left(left), right(right) {}
  ~Node() {
    delete left;
    delete right;
  }
};

// 优先队列比较规则重载
struct Compare {
  bool operator()(Node *left, Node *right) { return left->freq > right->freq; }
};

// 哈夫曼编码
void encode(Node *root, string str, unordered_map<char, string> &huffmanCode) {
  if (root == nullptr) {
    return;  // 不存在父节点时终止递归
  }
  if (!root->left && !root->right) {
    // 不存在子节点时，即当前节点为叶子节点，将编码赋值给节点
    huffmanCode[root->ch] = str;
  }
  // 递归调用编码，往左编码为0，往右编码为1
  encode(root->left, str + "0", huffmanCode);
  encode(root->right, str + "1", huffmanCode);
}

string decode(Node *root, string encodeText) {
  string res = "";
  Node *curr = root;
  for (char bit : encodeText) {
    if (bit == '0') {
      curr = curr->left;
    } else {
      curr = curr->right;
    }
    if (!curr->left && !curr->right) {
      res += curr->ch;
      curr = root;
    }
  }
  return res;
}

// 构建哈夫曼树
Node *buildHuffmanTree(string text) {
  unordered_map<char, int> freqs;  // 以char为key，每个char出现的频率为value
  for (char ch : text) {
    freqs[ch]++;  // 统计对应ch出现的次数
  }
  priority_queue<Node *, vector<Node *>, Compare>
      pq;  // 优先队列根据Compare规则自动排序
  for (auto pair : freqs) {
    // 迭代无序map集合中的数据，根据比较规则，较小的值先进
    pq.push(new Node(pair.first, pair.second));
  }
  while (pq.size() != 1) {  // 当优先队列中的数据至少超过1个
    Node *left = pq.top();  // 小的值放在左子树
    pq.pop();
    Node *right = pq.top();  // 次小的值放在右子树
    pq.pop();
    int sum = left->freq + right->freq;  // 计算次数之和，构造父节点
    pq.push(new Node('\0', sum, left, right));  // 父节点也会自动排序
  }
  return pq.top();
}

int main() {
  // 测试数据一: zhejiang university of technology, computer college
  // 测试数据二: 1310773597218806522025
  string text;
  getline(cin, text);

  // 找到根节点，用于后续对各个叶子节点进行递归编码
  Node *root = buildHuffmanTree(text);

  unordered_map<char, string> huffmanCode;  // 哈夫曼编码结果集
  encode(root, "", huffmanCode);

  cout << "哈夫曼编码: " << endl;
  for (auto pair : huffmanCode) {
    cout << pair.first << " " << pair.second << endl;
  }
  
  string encodeText = "";
  cout << "解码原始字符串: ";
  for (char ch : text) {
    encodeText += huffmanCode[ch];
  }
  cout << decode(root, encodeText) << endl;

  // 压缩前定长码的长度
  int len = 0;
  while (huffmanCode.size() > pow(2, len)) {
    len++;
  }
  int originalSize = text.length() * len;

  int compressedSize = 0;
  // 计算压缩后的编码总长度
  for (char ch : text) {
    compressedSize += huffmanCode[ch].length();
  }
  double compressionRatio = (double)compressedSize / originalSize;

  cout << "原始大小: " << originalSize << endl;

  cout << "压缩大小: " << compressedSize << endl;

  cout.precision(2);
  cout << "压缩比: " << compressionRatio * 100 << "%" << endl;

  delete root;
  return 0;
}
