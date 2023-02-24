#include "../include/rb_tree.h"

#include <cstddef>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <stack>
#include <string>

#include "../include/rb_tree.h"
#define FLAG '`'  // 特殊记号用于分隔姓名与密码
#define RED "red"
#define BLACK "black"

// 私有成员函数
// 遍历红黑树
void RBTree::print(Node *node) const {
  stack<Node *> stack;
  while (node || !stack.empty()) {
    // 将所有左子节点入栈
    while (node) {
      stack.push(node);
      node = node->getLeft();
    }
    // 如果左子节点不存在则本次输出父节点或右子节点，中序遍历输出
    node = stack.top();
    colorFormat(node);
    stack.pop();
    // 指向右子树，如果节点为空，则上面的寻左子节点也不会执行
    node = node->getRight();
  }
}

// 查询用户信息
Node *RBTree::search(Node *curr, string name) const {
  while (curr != nullptr) {
    if (curr->getUser().name.compare(name) < 0) {
      curr = curr->getLeft();
    } else if (curr->getUser().name.compare(name) > 0) {
      curr = curr->getRight();
    } else {
      break;
    }
  }
  return curr;
}

// 添加新用户
void RBTree::add(Node *newNode, Node *parent, Node *uncle) {
  // 没有父节点说明是根节点，直接添加即可
  if (parent == nullptr) {
    root = newNode;
    return;
  }

  // 非根节点处理
  // 判断新节点是左子树还是右子树
  if (newNode->getUser().name.compare(parent->getUser().name) < 0) {
    parent->setLeft(newNode);
    newNode->setParent(parent);
  } else {
    parent->setRight(newNode);
    newNode->setParent(parent);
  }
  // 颜色调整
  // 如果父节点是黑色，则不需要进行其他操作
  if (parent->getColor() == BLACK) {
    return;
  }
  // 如果父节点是红色，则需要分多种情况处理
  // 如果父节点是红色，那说明父节点肯定不是根节点，且一定存在祖父节点
  if (parent->getColor() == RED) {
    // 情况一：叔叔节点存在且为红节点，由于红黑树性质，红红不能相连，可以推断祖父节点为黑色
    // 红黑树性质：两个兄弟节点有一个为黑色节点，则另一个也为黑色
    // 因此父节点和叔叔节点需要变黑色，祖父节点需要进一步考虑
    Node *grand = parent->getParent();  // 祖父节点
    if (uncle != nullptr && uncle->getColor() == RED) {
      colorChange(parent);
      colorChange(uncle);

      // 关于祖父节点再进行分情况处理
      // 1.祖父节点是根节点，则保持黑色不变
      // 2.祖父节点不是根节点，根据其父节点做处理
      // 2.1.如果其父节点为黑色，则不需要进行处理
      // 2.2.如果其父节点为红色，则需要以祖父节点视为新的插入节点进行自平衡（旋转操作）
      if (grand != root && grand->getParent()->getColor() == RED) {
        // TODO:
        if (grand->getParent()->getLeft() == grand) {
          uncle = grand->getParent()->getRight();
        } else {
          uncle = grand->getParent()->getLeft();
        }
        add(grand, grand->getParent(), uncle);
      }

    } else if (uncle == nullptr && parent == grand->getLeft()) {
      // 情况二：叔叔节点不存在或为黑色叶子节点(nil)，且父节点是祖父节点的左子节点
      // 考虑插入节点与父节点的关系
      // 1.插入节点是父节点的左子节点，父节点、祖父节点变色，对祖父节点右旋
      if (newNode == parent->getLeft()) {
        colorChange(parent);
        colorChange(grand);
        rightRotate(parent, grand);
      } else {
        // 2.插入节点是父节点的右子节点，通过左旋可以直接转化到上一种情况
        leftRotate(newNode, parent);
        // 重复上一种情况的操作
        colorChange(parent);
        colorChange(grand);
        rightRotate(parent, grand);
      }
    } else if (uncle == nullptr && parent == grand->getRight()) {
      // 情况三：叔叔节点不存在或为黑色叶子节点(nil)，且父节点是祖父节点的右子节点
      // 考虑插入节点和父节点的关系
      // 1.插入节点是父节点的右子节点，父节点、祖父节点变色，对祖父节点左旋
      if (newNode == parent->getRight()) {
        colorChange(parent);
        colorChange(grand);
        leftRotate(parent, grand);
      } else {
        // 2.插入节点是父节点的右子节点，通过右旋可以直接转化到上一种情况
        rightRotate(newNode, parent);
        // 重复上一种情况的操作
        colorChange(parent);
        colorChange(grand);
        leftRotate(parent, grand);
      }
    }
  }
}

void RBTree::remove(Node *T) {
  Node *parent = nullptr;   // 记录父节点
  Node *brother = nullptr;  // 记录兄弟节点
  // 情况一：删除节点无子节点，直接删除即可
  if (T->getLeft() == nullptr && T->getRight() == nullptr) {
    T = nullptr;
    return;
  }
  // 情况二：删除节点有一个子节点，用子节点替换删除节点，并进一步讨论孙子节点情况
  if (T->getLeft() != nullptr && T->getRight() == nullptr) {
    parent = T;
    T = T->getLeft();
  }
  // 1.替换节点是红色节点，设置为删除节点的颜色即可，由于红黑树的性质，删除节点一定为黑节点
  if (T->getColor() == RED) {
    colorChange(T);
    return;
  } else if (T == parent->getLeft()) {
    // 2.替换节点是黑节点，进一步讨论
    // 2.1 替换节点是其父节点的左子节点
    // 2.1.1 替换节点的兄弟节点是红节点
    if (brother->getColor() == RED) {
      colorChange(brother);         // 将兄弟节点变色
      colorChange(parent);          // 将父节点变色
      leftRotate(brother, parent);  // 对父节点左旋
      // 通过以上操作，转化为2.1.2.3的情景，执行操作
      brother->setColor(RED);  // 将兄弟节点设为红色
      // 将替换节点的父节点作为新的替换节点重新处理
      remove(T->getParent());
    } else if (brother->getColor() == BLACK) {
      // 2.1.2 替换节点的兄弟节点是黑节点，进一步考虑子情况
      // 2.1.2.1 替换节点的兄弟节点的右子节点为红节点
      if (brother->getRight()->getColor() == RED) {
        brother->setColor(
            parent->getColor());  // 将兄弟节点的颜色与其父节点同步
        parent->setColor(BLACK);              // 将父节点设为黑色
        parent->getRight()->setColor(BLACK);  // 将兄弟节点的右子节点设为黑色
        leftRotate(brother, parent);  // 对父节点左旋

      } else if (brother->getRight()->getColor() == BLACK &&
                 brother->getLeft()->getColor() == RED) {
        // 2.1.2.2 替换节点的兄弟节点的右子节点为黑节点，左子节点为红节点
        brother->setColor(RED);               // 将兄弟节点设为红色
        brother->getLeft()->setColor(BLACK);  // 将兄弟节点的左子节点设为黑色
        rightRotate(brother->getLeft(), brother);  // 对兄弟节点右旋
        // 通过以上操作，转化为2.1.2.1的情景
        // 重复2.1.2.1的操作
        brother->setColor(
            parent->getColor());  // 将兄弟节点的颜色与其父节点同步
        parent->setColor(BLACK);              // 将父节点设为黑色
        parent->getRight()->setColor(BLACK);  // 将兄弟节点的右子节点设为黑色
        leftRotate(brother, parent);  // 对父节点左旋
      } else if (brother->getLeft()->getColor() == BLACK &&
                 brother->getRight()->getColor() == BLACK) {
        // 2.1.2.3 替换节点的兄弟节点的子节点全为黑色
        brother->setColor(RED);  // 将兄弟节点设为红色
        // 将替换节点的父节点作为新的替换节点重新处理
        remove(T->getParent());
      }
    }
  } else if (T == parent->getRight()) {
    // 2.2 替换节点是其父节点的右子节点
    // 2.2.1 替换节点的兄弟节点是红节点
    if (brother->getColor() == RED) {
      brother->setColor(BLACK);  // 将兄弟节点设为黑色
      parent->setColor(RED);     // 将父节点设为红色
      rightRotate(brother,
                  parent);  // 对替换节点右旋
      // 通过以上操作，转化为2.2.2.3的情景，执行操作
      brother->setColor(RED);  // 将兄弟节点设为红色
      // 将替换节点的父节点作为新的替换节点重新处理
      remove(T->getParent());
    } else if (brother->getColor() == BLACK) {
      // 2.2.2 替换节点的兄弟节点是黑节点，进一步考虑子情况
      if (brother->getLeft()->getColor() == RED) {
        // 2.2.2.1 替换节点的兄弟节点的左子节点是红节点
        brother->setColor(
            parent->getColor());  // 将兄弟节点的颜色与其父节点同步
        parent->setColor(BLACK);              // 将父节点设为黑色
        brother->getLeft()->setColor(BLACK);  // 将兄弟节点的左子节点设为黑色
        rightRotate(brother, parent);  // 对父节点右旋
      } else if (brother->getLeft()->getColor() == BLACK &&
                 brother->getRight()->getColor() == RED) {
        // 2.2.2.2 替换节点的兄弟节点的左子节点为黑节点，右子节点为红节点
        brother->setColor(RED);                // 将兄弟节点设为红色
        brother->getRight()->setColor(BLACK);  // 将兄弟节点的右子节点设为黑色
        leftRotate(brother->getRight(), brother);  // 对兄弟节点左旋
        // 通过以上操作，转化为2.2.2.1的情景，执行操作
        brother->setColor(
            parent->getColor());  // 将兄弟节点的颜色与其父节点同步
        parent->setColor(BLACK);              // 将父节点设为黑色
        brother->getLeft()->setColor(BLACK);  // 将兄弟节点的左子节点设为黑色
        rightRotate(brother, parent);  // 对父节点右旋
      } else if (brother->getLeft()->getColor() == BLACK &&
                 brother->getRight()->getColor() == BLACK) {
        // 2.2.2.3 替换节点的兄弟节点的子节点全为黑色
        brother->setColor(RED);  // 将兄弟节点设为红色
        // 将替换节点的父节点作为新的替换节点重新处理
        remove(T->getParent());
      }
    }
  }

  // 情况三：删除节点有两个子节点，用后继节点替换删除节点
  if (T->getLeft() != nullptr && T->getRight() != nullptr) {
    Node *tmp = T->getRight();    // 替换节点
    Node *parent = nullptr;       // 替换节点的父节点
    Node *left = T->getLeft();    // 暂存删除节点左子树的根节点
    Node *right = T->getRight();  // 暂存删除节点右子树的根节点
    // 找到后继节点
    while (tmp->getLeft() != nullptr) {
      parent = tmp;
      tmp = tmp->getLeft();
    }
    // 替换节点的父节点将左子节点设为其右子节点，如果不存在则为空
    parent->setLeft(tmp->getRight());
    // 替换节点的父节点设为删除节点的父节点
    tmp->setParent(T->getParent());
    // 替换节点的右子树设为删除节点的右子树
    tmp->setLeft(left);
    // 替换节点的右子树设为删除节点的右子树
    tmp->setRight(right);
    // 删除节点赋值为替换节点
    T = tmp;
    // 删除节点左右子树的父节点设为替换节点
    left->setParent(tmp);
    right->setParent(tmp);
  }
}

// 更新：将密码修改为新密码
void RBTree::update(Node *T, string name, string password) {
  T->getUser().password = password;
}

void RBTree::save(Node *T, ofstream &out) {
  // TODO:
}

// 公共函数

RBTree::RBTree(ifstream &in) {
  string str;  // 读取文件字符串
  int border;  // 记录分隔标志的位置
  Node *tmp;   // 节点

  while (in.peek() != EOF) {
    in >> str;
    str.find(FLAG);

    // 新建节点
    tmp = new Node(str.substr(0, FLAG),
                   str.substr(FLAG + 1, str.length() - FLAG - 1));
    if (root == nullptr) {
      // 第一个节点根节点为黑色
      tmp->setColor(BLACK);
    }
    root = tmp;
    // TODO:
  }
}

RBTree::RBTree(Node *node) { this->root = node; }

RBTree::RBTree() {}

RBTree::~RBTree() {}

// 节点颜色输出（红色）
void RBTree::colorFormat(Node *T) const {
  if (T->getColor() == RED) {
    cout << "\033[31;1m(" << T->getUser().name << ": " << T->getUser().password
         << ")\033[0m";
  } else {
    // 黑节点直接输出即可
    cout << "(" << T->getUser().name << ": " << T->getUser().password << ")";
  }
}

void RBTree::colorChange(Node *T) {
  if (T->getColor() == RED) {
    T->setColor(BLACK);
  } else {
    T->setColor(RED);
  }
}

void RBTree::print() const {
  Node *curr = root;
  print(curr);
}

Node *RBTree::search(string name, string password) const {
  Node *curr = root;
  if (curr == nullptr) {
    std::cout << "Not any data\n";
  } else {
    curr = search(curr, name);
  }

  if (curr != nullptr && curr->getUser().password.compare(name) == 0) {
    std::cout << "用户验证通过\n";
    return curr;
  } else {
    std::cout << "密码不匹配，验证失败\n";
  }
  return nullptr;
}

void RBTree::add(string name, string password) {
  Node *newNode = new Node(name, password);
  Node *parent;  // 父节点
  Node *uncle;   // 叔叔节点，即父节点的兄弟节点
  if (root != nullptr) {
    parent = root;
    newNode->setColor(RED);  // 默认插入节点为红色，避免打破红黑树平衡
  } else {  // 没有任何数据节点的情况下，直接添加到根节点
    newNode->setColor(BLACK);  // 根节点初始化为黑色
    add(newNode);
    return;
  }

  while (parent->getLeft() == nullptr && parent->getRight() == nullptr) {
    // 根据name进行排序
    // name小于父节点时，移动到左子树
    // name大于等于父节点时，移动到右子树
    if (parent->getUser().name.compare(name) < 0) {
      uncle = parent->getRight();
      parent = parent->getLeft();
    } else {
      uncle = parent->getLeft();
      parent = parent->getRight();
    }
  }
  // 循环结束后parent的地址实际上是新节点要添加的位置，回溯到上一个父节点
  parent = parent->getParent();
  add(newNode, parent, uncle);
}

void RBTree::remove(string name) {
  Node *curr = root;
  curr = search(curr, name);
  remove(curr);
}

// 更新：初步验证旧密码
void RBTree::update(string name, string password) {
  Node *target = search(root, name);
  if (target->getUser().password == password) {
    std::cout << "通过验证，请输入新密码\n";
    string passwd;
    std::cin >> passwd;
    update(target, name, passwd);
  }
}

void RBTree::save(ofstream &out) {
  // TODO:
}

// 左旋：提供一个右子节点和一个父节点
void RBTree::leftRotate(Node *node, Node *parent) {
  // 父节点围绕右子节点做左旋
  parent->setLeft(nullptr);              // 左子节点置空
  parent->setRight(nullptr);             // 右子节点置空
  node->setParent(parent->getParent());  // 右子节点的父节点设为祖父节点
  parent->setParent(node);  // 父节点的父节点设为其右子节点
  node->setLeft(parent);    // 将原来的父节点设为左子节点
  parent = node;            // 父节点赋值为右子节点
}

// 右旋：提供一个左子节点和一个父节点
void RBTree::rightRotate(Node *node, Node *parent) {
  // 父节点围绕左子节点做右旋
  parent->setLeft(nullptr);              // 左子节点置空
  parent->setRight(nullptr);             // 右子节点置空
  node->setParent(parent->getParent());  // 左子节点的父节点设为祖父节点
  parent->setParent(node);  // 父节点的父节点设为其左子节点
  node->setRight(node);     // 将原来的父节点设为右子节点
  parent = node;            // 父节点赋值为左子节点
}