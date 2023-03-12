#include <cstdio>
#include <iostream>

#include "../include/rb_tree.h"
#include "../include/user_data.h"
#include "rb_tree.cpp"
#include "user_data.cpp"

// 插入测试
void insert_test1() {
  // 1.红黑树为空树
  RBTree *root = new RBTree();
  root->add("abc", "11");
  root->print();
}

void insert_test2() {
  // 2.插入节点的父节点为黑节点
  RBTree *root = new RBTree();
  root->add("abc", "11");
  root->add("aac", "left");
  root->add("bbc", "right");
  root->print();
}

// 3.插入节点的父节点为红节点
void insert_test3_1() {
  // 3.1 叔叔节点存在且为红色
  RBTree *root = new RBTree();
  root->add("bbb", "11");
  root->add("aaa", "21");
  root->add("ccc", "22");
  root->add("ddd", "34");
  //   root->add("ggg", "48");

  // 复杂情况处理：递归处理父节点
//   root->add("aaa", "11");
//   root->add("ggg", "22");
//   root->add("ddd", "33");
//   root->add("bbb", "32");
//   root->add("fff", "33");
//   root->add("jjj", "34");
//   root->add("kkk", "4-16");
//   root->add("iii", "4-15");
//   root->add("lll", "5-32");
  root->print();
}

void insert_test3_2_1() {
  // 3.2 叔叔节点不存在或为黑节点，且插入节点的父节点是祖父节点的左子节点
  // 3.2.1 插入节点是其父节点的左子节点
  RBTree *root = new RBTree();
  root->add("ccc", "11");
  root->add("bbb", "21");
  root->add("aaa", "31");
  root->print();
}

void insert_test3_2_2() {
  // 3.2.2插入节点是其父节点的右子节点
  RBTree *root = new RBTree();
  root->add("ddd", "11");
  root->add("bbb", "21");
  root->add("ccc", "32");
  root->print();
}

void insert_test3_3_1() {
  // 3.3 叔叔节点不存在或为黑节点，且插入节点的父节点是祖父节点的右子节点
  // 3.3.1 插入节点是其父节点的右子节点
  RBTree *root = new RBTree();
  root->add("aaa", "11");
  root->add("bbb", "22");
  root->add("ccc", "34");
  root->print();
}

void insert_test3_3_2() {
  // 3.3.2 插入节点是其父节点的左子节点
  RBTree *root = new RBTree();
  root->add("aaa", "11");
  root->add("ccc", "22");
  root->add("bbb", "33");
  root->print();
}

void delete_test1() {
  // 1.替代节点是红节点
  RBTree *root = new RBTree();
  root->add("aaa", "11");
  root->add("bbb", "22");
  root->remove("aaa");
  root->print();
}

void delete_test2_1_1() {
  // 2.替代节点是黑节点，进一步考虑
  // 2.1 替代节点是父节点的左子节点
  // 2.1.1 替代节点的兄弟节点是红节点
  RBTree *root = new RBTree();
  root->add("aaa", "11");
  root->add("bbb", "22");
  root->add("ccc", "34");
  root->add("ddd", "34");
  root->add("eee", "48");
  root->add("fff", "4-16");
  root->add("ggg", "5-32");
  root->add("hhh", "5-32");
  root->add("iii", "5-32");
  root->add("jjj", "5-32");
  root->remove("ddd");
  root->print();
}

void delete_test2_1_2_1() {
  // 2.1.2 替代节点的兄弟节点是黑节点
  // 2.1.2.1 替代节点的兄弟节点的右子节点是红节点，左子节点任意颜色
  RBTree *root = new RBTree();
  root->add("aaa", "11");
  root->add("ggg", "22");
  root->add("ddd", "33");
  root->add("bbb", "32");
  root->add("fff", "33");
  root->add("jjj", "34");
  root->add("kkk", "4-16");
  root->remove("ddd");
  root->print();
}

void delete_test2_1_2_2() {
  // 2.1.2.2 替代节点的兄弟节点的右子节点是黑节点，左子节点是红节点
  RBTree *root = new RBTree();
  root->add("aaa", "11");
  root->add("ggg", "22");
  root->add("ddd", "33");
  root->add("bbb", "32");
  root->add("fff", "33");
  root->add("jjj", "34");
  root->add("kkk", "4-16");
  // TODO:

// root->add("")
// root->add("mmm")
//  root->add("nnn"); 
}

void delete_test2_1_2_3() {
  // 2.1.2.3 替代节点的兄弟节点的子节点全为黑色
}

void delete_test2_2_1() {
  // 2.2 替代节点是其父节点的右子节点
  // 2.2.1 替代节点的兄弟节点是红节点
}

void delete_test2_2_2_1() {
  // 2.2.2 替代节点的兄弟节点是黑节点
  // 2.2.2.1 替代节点的兄弟节点的左子节点是红节点，右子节点任意颜色
}

void delete_test2_2_2_2() {
  // 2.2.2.2 替代节点的兄弟节点的左子节点是黑节点，右子节点是红节点
}

void delete_test2_2_2_3() {
  // 2.2.2.3 替代节点的兄弟节点的子节点都是黑节点
}

void add_test() {
  RBTree *rbTree = new RBTree();
  rbTree->add("eee", "111");
  rbTree->add("ccc", "222");

  rbTree->add("aaa", "444");
  rbTree->add("eee", "555");
  rbTree->add("fff", "666");
  rbTree->add("ggg", "777");
  rbTree->add("hhh", "888");
  rbTree->add("iii", "999");
  rbTree->add("jjj", "333");
  rbTree->print();
}

void update_test() {
  string name, pass;
  RBTree *root = new RBTree();
  root->add("hello", "112");

  cout << "请输入要修改密码的用户名： ";
  cin >> name;
  cout << "请输入旧密码： ";
  cin >> pass;
  Node *res = root->update(name, pass);
  if (res != nullptr) {
    cout << res->getUser().name << ": " << res->getUser().password;
  }
}

void test(Node *a, Node *b) { a->setLeft(b); }

int main() {
//   insert_test1();
  insert_test2();

//   insert_test3_1();
//   insert_test3_2_1();
    // insert_test3_2_2();

//   insert_test3_3_1();
//   insert_test3_3_2();

    // delete_test1();
  //
  // TODO:
//   delete_test2_1_1();

  // delete_test2_1_2_1();

//   delete_test2_1_2_2();

  //   update_test();

  return 0;
}