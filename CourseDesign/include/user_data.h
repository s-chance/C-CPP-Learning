#ifndef USER_DATA_H
#define USER_DATA_H

#include <string>
using namespace std;

// 用户信息
struct User {
  string name;
  string password;
};

// 数据节点
class Node {
 private:
  User user;                               // 用户信息
  string color;                            // 节点颜色
  Node *parent = nullptr;                  // 父节点
  Node *left = nullptr, *right = nullptr;  // 左右子节点

 public:
  Node(string name, string password);
  Node();   // 无参构造函数
  ~Node();  // 析构函数

  // getter
  string getColor();  // 获取节点颜色
  User &getUser();    // 获取用户信息
  Node *getParent();  // 获取父节点
  Node *getLeft();    // 获取左子节点
  Node *getRight();   // 获取右子节点

  // setter
  void setColor(string color);                 // 设置节点颜色
  void setUser(string name, string password);  // 设置用户信息
  void setParent(Node *node);                  // 设置父节点
  void setLeft(Node *node);                    // 设置左子节点
  void setRight(Node *node);                   // 设置右子节点
};
#endif