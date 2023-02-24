#include "../include/rb_tree.h"
#include "../include/user_data.h"
#include "rb_tree.cpp"
#include "user_data.cpp"

void add_test() {
  Node *newNode1 = new Node("aaa", "111");
  Node *newNode2 = new Node("bbb", "222");
  Node *newNode3 = new Node("ccc", "333");
  RBTree *rbTree = new RBTree();
  rbTree->add("aaa", "111");
  rbTree->add("bbb", "222");
  //   rbTree->add("ccc", "333");
  rbTree->print();
}

int main() {
  add_test();
  return 0;
}