
#include "../include/user_data.h"

#include <string>

Node::Node(string name, string password) {
  this->user.name = name;
  this->user.password = password;
}

Node::Node() {}

Node::~Node() {}

// getter
int Node::getBF() { return this->bf; }

string Node::getColor() { return this->color; }

User &Node::getUser() { return user; }

Node *Node::getParent() { return this->parent; }

Node *Node::getLeft() { return this->left; }

Node *Node::getRight() { return this->right; }

// setter
void Node::setBF(int bf) { this->bf = bf; }

void Node::setColor(string color) { this->color = color; }

void Node::setUser(string name, string password) {
  this->user.name = name;
  this->user.password = password;
}

void Node::setParent(Node *node) { this->parent = node; }

void Node::setLeft(Node *node) { this->left = node; }

void Node::setRight(Node *node) { this->right = node; }
