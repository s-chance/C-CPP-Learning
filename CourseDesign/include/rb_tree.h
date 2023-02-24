#ifndef RB_TREE_H
#define RB_TREE_H

#include <fstream>
#include <string>

#include "user_data.h"

class RBTree {
 private:
  Node *root = nullptr;

  void print(Node *node) const;              // 打印二叉树
  Node *search(Node *T, string name) const;  // 查询用户
  void add(Node *newNode, Node *parent = nullptr,
           Node *uncle = nullptr);                     // 添加用户
  void remove(Node *T);                                // 删除用户
  void update(Node *T, string name, string password);  // 更新密码
  void save(Node *T, ofstream &out);                   // 持久化

 public:
  RBTree(ifstream &in);
  RBTree(Node *node);  // 测试用构造函数
  RBTree();            // 无参构造函数
  ~RBTree();

  void colorFormat(Node *T) const;  // 节点颜色格式输出
  void colorChange(Node *T);        // 变色

  void print() const;  // 打印

  Node *search(string name, string password) const;  // 查询

  void add(string name, string password);  // 添加

  void remove(string name);  // 删除

  void update(string name, string password);  // 更新

  void save(ofstream &out);  // 持久化

  void leftRotate(Node *node, Node *parent);   // 左旋
  void rightRotate(Node *node, Node *parent);  // 右旋
};

#endif