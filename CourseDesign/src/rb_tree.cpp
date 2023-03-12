#include "../include/rb_tree.h"

#include <cstddef>
#include <cstdio>
#include <fstream>
#include <iostream>
#include <stack>
#include <string>
#include <vector>

#include "../include/rb_tree.h"
#define FLAG '`'  // 特殊记号用于分隔姓名与密码
#define RED "red"
#define BLACK "black"

// 私有成员函数
// 遍历红黑树
void RBTree::print(Node *node) const {
  if (node == nullptr) {
    std::cout << "not any data!\n";
    return;
  }
  vector<Node *> ans;
  stack<Node *> stack;
  while (node || !stack.empty()) {
    // 将所有左子节点入栈
    while (node) {
      stack.push(node);
      node = node->getLeft();
    }
    // 如果左子节点不存在则本次输出父节点或右子节点，中序遍历输出
    if (!stack.empty()) {
      node = stack.top();
      ans.push_back(node);
      colorFormat(node);
      stack.pop();
    } else {
      colorFormat(node);
      ans.push_back(node);
    }
    // 指向右子树，如果节点为空，则上面的寻左子节点也不会执行
    node = node->getRight();
  }
}

// 查询用户信息：通过name查询到用户信息，并返回用户信息的对应节点，如果用户不存在则返回的是空节点
Node *RBTree::search(Node *curr, string name) const {
  while (curr != nullptr) {
    if (name.compare(curr->getUser().name) < 0) {
      curr = curr->getLeft();
    } else if (name.compare(curr->getUser().name) > 0) {
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
      colorChange(grand);

      // 关于祖父节点再进行分情况处理
      // 1.祖父节点是根节点，则保持黑色不变
      // 2.祖父节点不是根节点，根据其父节点做处理
      // 2.1.如果其父节点为黑色，则不需要进行处理
      // 2.2.如果其父节点为红色，则需要以祖父节点视为新的插入节点进行自平衡（旋转操作）
      if (grand != root && grand->getParent()->getColor() == RED) {
        if (grand->getParent()->getParent()->getLeft() == grand->getParent()) {
          uncle = grand->getParent()->getParent()->getRight();
        } else if (grand->getParent()->getParent()->getRight() ==
                   grand->getParent()) {
          uncle = grand->getParent()->getParent()->getLeft();
        }
        add(grand, grand->getParent(), uncle);
      } else if (grand == root) {
        colorChange(grand);  // 重新将祖父节点（根节点）设为黑色
      }
    } else if ((uncle == nullptr || uncle->getColor() == BLACK) &&
               parent == grand->getLeft()) {
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
        // grand->setLeft(newNode);  // 将替换结果同步到红黑树
        // 重复上一种情况的操作
        colorChange(newNode);
        colorChange(grand);
        rightRotate(newNode, grand);
      }
    } else if ((uncle == nullptr || uncle->getColor() == BLACK) &&
               parent == grand->getRight()) {
      // 情况三：叔叔节点不存在或为黑色叶子节点(nil)，且父节点是祖父节点的右子节点
      // 考虑插入节点和父节点的关系
      // 1.插入节点是父节点的右子节点，父节点、祖父节点变色，对祖父节点左旋
      if (newNode == parent->getRight()) {
        colorChange(parent);
        colorChange(grand);
        leftRotate(parent, grand);
        // grand->getParent()->setRight(newNode);  // 将替换结果同步到红黑树
      } else if (newNode == parent->getLeft()) {
        // 2.插入节点是父节点的左子节点，通过右旋可以直接转化到上一种情况
        rightRotate(newNode, parent);
        // grand->setRight(newNode);  // 将替换结果同步到红黑树
        // 重复上一种情况的操作
        colorChange(newNode);
        colorChange(grand);
        leftRotate(newNode, grand);
      }
    }
  }
}

// 删除实现：提供一个删除节点和替换节点
void RBTree::remove(Node *target) {
  Node *tmp = root;         // 用于找到红黑树中需要删除的节点
  Node *tparent = nullptr;  // 删除节点的父节点
  while (target != nullptr) {
    if (target->getUser().name.compare(tmp->getUser().name) < 0) {
      tparent = tmp;
      tmp = tmp->getLeft();
    } else if (target->getUser().name.compare(tmp->getUser().name) > 0) {
      tparent = tmp;
      tmp = tmp->getRight();
    } else {
      break;
    }
  }

  // 情况一：删除节点无子节点，直接删除即可
  if (tmp->getLeft() == nullptr && tmp->getRight() == nullptr) {
    if (tparent != nullptr && tmp == tparent->getLeft()) {
      tparent->setLeft(nullptr);
    } else if (tparent != nullptr && tmp == tparent->getRight()) {
      tparent->setRight(nullptr);
    } else {
      // 删除节点的父节点不存在，说明要删除的是根节点
      root = nullptr;
    }
    return;
  }
  // 其余情况：删除节点至少存在一个子节点

  // 寻找替代节点
  Node *replace = nullptr;  // 记录替换节点
  Node *parent = nullptr;   // 记录替代节点的父节点
  Node *brother = nullptr;  // 记录替代节点的兄弟节点

  // 找到替换节点，删除节点的前继节点或后继节点
  if (tmp->getLeft() != nullptr && tmp->getRight() == nullptr) {
    // 删除节点只有左子树,则往左子树找前继节点
    replace = tmp->getLeft();
    while (replace->getRight() != nullptr) {
      parent = replace;
      brother = replace->getLeft();
      replace = replace->getRight();  // 前继节点
    }

  } else {
    // 其余情况，只有右子树或者左右子树都有，则往右子树找后继节点
    replace = tmp->getRight();
    while (replace->getLeft() != nullptr) {
      parent = replace;
      brother = replace->getRight();
      replace = replace->getLeft();  // 后继节点
    }
  }

  // 情况二：删除节点有一个子节点，用子节点替换删除节点
  //   if (replace->getLeft() != nullptr && replace->getRight() == nullptr) {
  //     replace = tmp->getRight();
  //   } else if (tmp->getLeft() == nullptr && tmp->getRight() != nullptr) {
  //     replace = tmp->getLeft();
  //   } else if (tmp->getLeft() != nullptr && tmp->getRight() != nullptr) {
  //     // 情况三：删除节点有两个子节点，用后继节点替换删除节点
  //     replace = tmp->getRight();  // 替换节点，先移入右子树

  //     // Node *left = tmp->getLeft();      // 暂存删除节点左子树的根节点
  //     // Node *right = tmp->getRight();    // 暂存删除节点右子树的根节点
  //     // 找到后继节点
  //     while (replace->getLeft() != nullptr) {
  //       parent = replace;
  //       brother = replace->getRight();
  //       replace = replace->getLeft();
  //     }

  // parent->setLeft(nullptr); //

  // // 替换节点的父节点将左子节点设为其右子节点，如果不存在则为空
  // parent->setLeft(tmp->getRight());
  // // 替换节点的父节点设为删除节点的父节点
  // tmp->setParent(T->getParent());
  // // 替换节点的右子树设为删除节点的右子树
  // tmp->setLeft(left);
  // // 替换节点的右子树设为删除节点的右子树
  // tmp->setRight(right);
  // // 删除节点赋值为替换节点
  // T = tmp;
  // // 删除节点左右子树的父节点设为替换节点
  // left->setParent(tmp);
  // right->setParent(tmp);
  //   }

  // 作为中间指针，在旋转操作后调整父节点和兄弟节点的数据
  // 同时用于判断旋转操作是否已经执行，实现在修改了节点的情况下执行正确的流程控制
  //   Node *t = nullptr;

  // 删除及自平衡处理
  // 替换节点的深度一定大于删除节点的深度
  while (tmp != replace) {
    // 1.替换节点是红色节点，设置为删除节点的颜色即可
    // 这是唯一不需要进行自平衡的情况
    if (replace->getColor() == RED) {//FIXME:
      // 情况二：删除节点有一个子节点，用子节点替换删除节点
      // 处理前继节点存在左子节点的情况
      if (replace->getLeft() != nullptr && replace->getRight() == nullptr) {
        parent->setRight(replace->getLeft());
        replace->getLeft()->setParent(parent);
      } else if (parent != nullptr) {
        parent->setRight(nullptr);
      }

      // 处理后继节点存在右子节点的情况
      if (replace->getRight() != nullptr && replace->getLeft() == nullptr) {
        parent->setLeft(replace->getRight());
        replace->getRight()->setParent(parent);
      } else if (parent != nullptr) {
        parent->setLeft(nullptr);
      }

      replace->setColor(tmp->getColor());

      // 将删除节点用替换节点替代
      // 以下判断主要用于避免替换节点和删除节点是相连节点而导致死循环的问题
      if (replace != tmp->getLeft()) {
        replace->setLeft(tmp->getLeft());
      }
      if (replace != tmp->getRight()) {
        replace->setRight(tmp->getRight());
      }
      replace->setParent(tmp->getParent());

      // 删除节点
      if (tparent != nullptr && tmp == tparent->getLeft()) {
        tparent->setLeft(replace);
        break;
      } else if (tparent != nullptr && tmp == tparent->getRight()) {
        tparent->setRight(replace);
        break;
      } else {
        // 要删除的是根节点
        root = replace;
        break;
      }
    } else if (replace == parent->getLeft()) {
      // 2.替换节点是黑节点，进一步讨论
      // 2.1 替换节点是其父节点的左子节点
      // 2.1.1 替换节点的兄弟节点是红节点
      if (brother->getColor() == RED) {
        colorChange(brother);         // 将兄弟节点变色
        colorChange(parent);          // 将父节点变色
        leftRotate(brother, parent);  // 对父节点左旋

        Node *t =
            brother->getRight();  // 保存兄弟节点（新的父节点）的右子树部分
        brother = parent->getRight();  // 旋转操作后获取新的兄弟节点
        // t->setRight(parent->getParent());
        // parent = t->getParent();
        //  通过以上操作，转化为2.1.2.3的情景进入下一轮循环执行操作 FIXME:

        // continue;
        // brother->setColor(RED);  // 将兄弟节点设为红色以支持自平衡

        // // 将替换节点的父节点作为新的替换节点重新处理
        // replace = replace->getParent();
      } else if (brother->getColor() == BLACK) {
        // 2.1.2 替换节点的兄弟节点是黑节点，进一步考虑子情况
        // 2.1.2.1 替换节点的兄弟节点的右子节点为红节点
        if (brother->getRight() != nullptr &&
            brother->getRight()->getColor() == RED) {
          brother->setColor(
              parent->getColor());  // 将兄弟节点的颜色与其父节点同步
          parent->setColor(BLACK);  // 将父节点设为黑色
          brother->getRight()->setColor(BLACK);  // 将兄弟节点的右子节点设为黑色
          leftRotate(brother, parent);  // 对父节点左旋

          // 情况二：删除节点有一个子节点，用子节点替换删除节点
          // 处理前继节点存在左子节点的情况
          if (replace->getLeft() != nullptr) {
            parent->setRight(replace->getLeft());
            replace->getLeft()->setParent(parent);
          } else if (parent != nullptr) {
            parent->setRight(nullptr);
          }

          // 处理后继节点存在右子节点的情况
          if (replace->getRight() != nullptr) {
            parent->setLeft(replace->getRight());
            replace->getRight()->setParent(parent);
          } else if (parent != nullptr) {
            parent->setLeft(nullptr);
          }

          // 将删除节点用替换节点替代
          // 以下判断主要用于避免替换节点和删除节点是相连节点而导致死循环的问题
          if (replace != tmp->getLeft()) {
            replace->setLeft(tmp->getLeft());
          }
          if (replace != tmp->getRight()) {
            replace->setRight(tmp->getRight());
          }
          replace->setParent(tmp->getParent());

          // 删除节点
          if (tparent != nullptr && tmp == tparent->getLeft()) {
            tparent->setLeft(replace);
            break;
          } else if (tparent != nullptr && tmp == tparent->getRight()) {
            tparent->setRight(replace);
            break;
          } else {
            // 要删除的是根节点
            root = replace;
            break;
          }

        } else if (brother->getRight() != nullptr &&
                   brother->getRight()->getColor() == BLACK &&
                   brother->getLeft() != nullptr &&
                   brother->getLeft()->getColor() == RED) {
          // 2.1.2.2 替换节点的兄弟节点的右子节点为黑节点，左子节点为红节点
          brother->setColor(RED);               // 将兄弟节点设为红色
          brother->getLeft()->setColor(BLACK);  // 将兄弟节点的左子节点设为黑色
          rightRotate(brother->getLeft(), brother);  // 对兄弟节点右旋
          // 通过以上操作，转化为2.1.2.1的情景进入下一轮循环执行操作 FIXME:

          //   continue;
          //   brother->setColor(
          //       parent->getColor());  // 将兄弟节点的颜色与其父节点同步
          //   parent->setColor(BLACK);  // 将父节点设为黑色
          //   parent->getRight()->setColor(BLACK);  //
          //   将兄弟节点的右子节点设为黑色 leftRotate(brother, parent);  //
          //   对父节点左旋
        } else if ((brother->getLeft() == nullptr ||
                    brother->getLeft()->getColor() == BLACK) &&
                   (brother->getRight() == nullptr ||
                    brother->getRight()->getColor() == BLACK)) {
          // 2.1.2.3 替换节点的兄弟节点的子节点全为黑色
          brother->setColor(RED);  // 将兄弟节点设为红色

          // 将替换节点的父节点作为新的删除节点重新处理
          // 找到新的替换节点及其父节点和兄弟节点
          replace = replace->getParent();
          parent = replace->getParent();
          if (replace == parent->getLeft()) {
            brother = parent->getRight();
          } else if (replace == parent->getRight()) {
            brother = parent->getLeft();
          }
        }
      }
    } else if (replace == parent->getRight()) {
      // 2.2 替换节点是其父节点的右子节点
      // 2.2.1 替换节点的兄弟节点是红节点
      if (brother != nullptr && brother->getColor() == RED) {
        brother->setColor(BLACK);      // 将兄弟节点设为黑色
        parent->setColor(RED);         // 将父节点设为红色
        rightRotate(brother, parent);  // 对替换节点右旋

        brother = parent->getLeft();  // 旋转操作后获取新的兄弟节点
        // 通过以上操作，转化为2.2.2.3的情景进入下一轮循环执行操作 FIXME:
        // continue;
        // brother->setColor(RED);  // 将兄弟节点设为红色
        // // 将替换节点的父节点作为新的替换节点重新处理
        // remove(T->getParent());
      } else if (brother->getColor() == BLACK) {
        // 2.2.2 替换节点的兄弟节点是黑节点，进一步考虑子情况
        if (brother->getLeft()->getColor() == RED) {
          // 2.2.2.1 替换节点的兄弟节点的左子节点是红节点
          brother->setColor(
              parent->getColor());  // 将兄弟节点的颜色与其父节点同步
          parent->setColor(BLACK);  // 将父节点设为黑色
          brother->getLeft()->setColor(BLACK);  // 将兄弟节点的左子节点设为黑色
          rightRotate(brother, parent);  // 对父节点右旋

          // 情况二：删除节点有一个子节点，用子节点替换删除节点
          // 处理前继节点存在左子节点的情况
          if (replace->getLeft() != nullptr) {
            parent->setRight(replace->getLeft());
            replace->getLeft()->setParent(parent);
          } else if (parent != nullptr) {
            parent->setRight(nullptr);
          }

          // 处理后继节点存在右子节点的情况
          if (replace->getRight() != nullptr) {
            parent->setLeft(replace->getRight());
            replace->getRight()->setParent(parent);
          } else if (parent != nullptr) {
            parent->setLeft(nullptr);
          }

          // 将删除节点用替换节点替代
          // 以下判断主要用于避免替换节点和删除节点是相连节点而导致死循环的问题
          if (replace != tmp->getLeft()) {
            replace->setLeft(tmp->getLeft());
          }
          if (replace != tmp->getRight()) {
            replace->setRight(tmp->getRight());
          }
          replace->setParent(tmp->getParent());

          // 删除节点
          if (tparent != nullptr && tmp == tparent->getLeft()) {
            tparent->setLeft(replace);
            break;
          } else if (tparent != nullptr && tmp == tparent->getRight()) {
            tparent->setRight(replace);
            break;
          } else {
            // 要删除的是根节点
            root = replace;
            break;
          }
        } else if (brother->getLeft()->getColor() == BLACK &&
                   brother->getRight()->getColor() == RED) {
          // 2.2.2.2 替换节点的兄弟节点的左子节点为黑节点，右子节点为红节点
          brother->setColor(RED);                // 将兄弟节点设为红色
          brother->getRight()->setColor(BLACK);  // 将兄弟节点的右子节点设为黑色
          leftRotate(brother->getRight(), brother);  // 对兄弟节点左旋
          // 通过以上操作，转化为2.2.2.1的情景进入下一轮循环执行操作 FIXME:
          //   continue;
          //   brother->setColor(
          //       parent->getColor());  // 将兄弟节点的颜色与其父节点同步
          //   parent->setColor(BLACK);  // 将父节点设为黑色
          //   brother->getLeft()->setColor(BLACK);  //
          //   将兄弟节点的左子节点设为黑色 rightRotate(brother, parent);  //
          //   对父节点右旋
          //   continue;
        } else if (brother->getLeft()->getColor() == BLACK &&
                   brother->getRight()->getColor() == BLACK) {
          // 2.2.2.3 替换节点的兄弟节点的子节点全为黑色
          brother->setColor(RED);  // 将兄弟节点设为红色

          // 将替换节点的父节点作为新的删除节点重新处理
          // 找到新的替换节点及其父节点和兄弟节点
          replace = replace->getParent();
          parent = replace->getParent();
          if (replace == parent->getLeft()) {
            brother = parent->getRight();
          } else if (replace == parent->getRight()) {
            brother = parent->getLeft();
          }
        }
      }
    }
  }
}

// 更新：将密码修改为新密码
Node *RBTree::update(Node *target, string name, string password) {
  target->getUser().password = password;
  std::cout << "密码成功更新!\n";
  return target;
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

// 查询：实现用户验证
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
// 新增
void RBTree::add(string name, string password) {
  Node *newNode = new Node(name, password);

  // 没有任何数据节点的情况下，直接添加到根节点
  if (root == nullptr) {
    newNode->setColor(BLACK);  // 根节点初始化为黑色
    root = newNode;
    return;
  } else {
    newNode->setColor(RED);  // 默认插入节点为红色，避免打破红黑树平衡
  }

  Node *curr = root;       // 当前节点
  Node *parent = nullptr;  // 父节点
  Node *uncle = nullptr;   // 叔叔节点，即父节点的兄弟节点
  Node *grand = nullptr;   // 祖父节点用于寻找父节点的兄弟节点

  // 找到插入节点的空位
  // curr为空表示已找到插入节点位置
  while (curr != nullptr) {
    parent = curr;
    grand = curr->getParent();
    // 根据name进行排序
    // name小于父节点时，移动到左子树
    // name大于等于父节点时，移动到右子树
    if (name.compare(curr->getUser().name) < 0) {
      curr = curr->getLeft();
    } else {
      curr = curr->getRight();
    }
  }
  // 找到叔叔节点
  if (grand != nullptr && parent == grand->getLeft()) {
    uncle = grand->getRight();
  } else if (grand != nullptr && parent == grand->getRight()) {
    uncle = grand->getLeft();
  }

  add(newNode, parent, uncle);
}

void RBTree::remove(string name) {
  Node *curr = nullptr;
  curr = search(root, name);
  remove(curr);
}

// 更新：初步验证旧密码
Node *RBTree::update(string name, string password) {
  Node *target = search(root, name);
  if (target != nullptr && target->getUser().password == password) {
    std::cout << "通过验证，请输入新密码：";
    string passwd;
    std::cin >> passwd;
    return update(target, name, passwd);
  } else {
    std::cout << "用户名或密码错误\n";
  }
  return nullptr;
}

void RBTree::save(ofstream &out) {
  // TODO:
}

// 左旋：提供一个右子节点和一个父节点
void RBTree::leftRotate(Node *node, Node *parent) {
  // 父节点围绕右子节点做左旋

  Node *tmp = root;  // 从根节点开始找到旋转节点
  while (tmp != nullptr) {
    if (node->getUser().name.compare(tmp->getUser().name) < 0) {
      parent = tmp;
      tmp = tmp->getLeft();
    } else if (node->getUser().name.compare(tmp->getUser().name) > 0) {
      parent = tmp;
      tmp = tmp->getRight();
    } else {
      break;
    }
  }

  node = tmp;
  Node *grand = parent->getParent();     // 获取祖父节点
  node->setParent(parent->getParent());  // 调整旋转节点的父节点指向
  parent->setParent(node);  // 父节点的父节点设为i旋转节点
  parent->setRight(
      node->getLeft());  // 父节点原来的右子节点设为其右子节点的左子节点
  node->setLeft(parent);  // 旋转节点的左子节点设为其父节点

  // 考虑祖父节点为空的情况以及原来的父节点与祖父节点的关系
  // 主要用于处理左右旋或者右左旋时可能出现的问题
  if (grand != nullptr && parent == grand->getRight()) {
    grand->setRight(node);  // 将原来的父节点设为旋转节点
  } else if (grand != nullptr && parent == grand->getLeft()) {
    grand->setLeft(node);  // 针对左右旋的处理
  } else {
    root = node;  // 祖父节点为空，则直接将根节点设为旋转节点
  }

  //   Node *tmp = parent;  // 暂存父节点
  //   if (parent->getParent() == nullptr) {
  //     root = node;  // 如果父节点为根节点，则直接将根节点赋值为右子节点
  //   } else {
  //     parent = node;  // 父节点赋值为右子节点
  //   }
  //   tmp->setLeft(nullptr);              // 左子节点置空
  //   tmp->setRight(nullptr);             // 右子节点置空
  //   node->setParent(tmp->getParent());  // 右子节点的父节点设为祖父节点
  //   node->setLeft(tmp);                 // 将原来的父节点设为左子节点
  //   tmp->setParent(node);  // 父节点的父节点设为其右子节点
}

// 右旋：提供一个左子节点和一个父节点
void RBTree::rightRotate(Node *node, Node *parent) {
  // 父节点围绕左子节点做右旋

  Node *tmp = root;  // 从根节点开始找到旋转节点
  while (tmp != nullptr) {
    if (node->getUser().name.compare(tmp->getUser().name) < 0) {
      parent = tmp;
      tmp = tmp->getLeft();
    } else if (node->getUser().name.compare(tmp->getUser().name) > 0) {
      parent = tmp;
      tmp = tmp->getRight();
    } else {
      break;
    }
  }

  node = tmp;
  Node *grand = parent->getParent();     // 获取祖父节点
  node->setParent(parent->getParent());  // 调整旋转节点的父节点指向
  parent->setParent(node);  // 父节点的父节点设为i旋转节点
  parent->setLeft(
      node->getRight());  // 父节点原来的左子节点设为其左子节点的右子节点
  node->setRight(parent);  // 旋转节点的右子节点设为其父节点

  // 考虑祖父节点为空的情况以及原来的父节点与祖父节点的关系
  // 主要用于处理左右旋或者右左旋时可能出现的问题
  if (grand != nullptr && parent == grand->getLeft()) {
    grand->setLeft(node);  // 将原来的父节点设为旋转节点
  } else if (grand != nullptr && parent == grand->getRight()) {
    grand->setRight(node);  // 针对右左旋的处理
  } else {
    root = node;  // 祖父节点为空，则直接将根节点设为旋转节点
  }
  //   Node *tmp = parent;  // 暂存父节点
  //   if (parent->getParent() == nullptr) {
  //     root = node;  // 如果父节点为根节点，则直接将根节点赋值为左子节点
  //   } else {
  //     // parent = root;
  //     // while (parent != tmp) {
  //     //   if (parent->getParent()) {

  //     //   }
  //     // }
  //     parent = node;  // 父节点赋值为左子节点
  //   }
  //   tmp->setLeft(nullptr);              // 左子节点置空
  //   tmp->setRight(nullptr);             // 右子节点置空
  //   node->setParent(tmp->getParent());  // 左子节点的父节点设为祖父节点
  //   node->setRight(tmp);                // 将原来的父节点设为右子节点
  //   tmp->setParent(node);  // 父节点的父节点设为其左子节点
}