#include "linkedList.hpp"

#include <iostream>

linked_list::linked_list() : size(0) { head = tail = new node(0); }

linked_list::linked_list(const linked_list& other) : size(other.size) {
  head = tail = new node(0);
  for (node* p = other.head->next; p; p = p->next) {
    tail->next = new node(p->data);
    tail = tail->next;
  }
}

linked_list& linked_list::operator=(const linked_list& other) {
  if (this == &other) {
    return *this;
  } else {
    delete[] head;
    size = other.size;
    head = tail = new node(0);
    for (node* p = other.head->next; p; p = p->next) {
      tail->next = new node(p->data);
      tail = tail->next;
    }
    return *this;
  }
}

int linked_list::list_size() const { return size; }

linked_list linked_list::operator+(const linked_list& right) {
  linked_list res = *this;
  for (node* p = right.head->next; p; p = p->next) {
    bool flag = true;
    for (node* q = res.head->next; q; q = q->next) {
      if (p->data == q->data) {
        flag = false;
        break;
      }
    }
    if (flag) {
      node* newNode = new node(p->data);
      res.tail->next = newNode;
      res.tail = newNode;
      res.size++;
    }
  }
  res.tail->next = nullptr;
  return res;
}

linked_list linked_list::operator-(const linked_list& right) {
  linked_list res = *this;
  for (node* p = right.head->next; p; p = p->next) {
    node* pre = res.head;
    node* q = res.head->next;
    while (q) {
      if (p->data == q->data) {
        pre->next = q->next;
        delete q;
        q = pre->next;
        res.size--;
      } else {
        pre = pre->next;
        q = pre->next;
      }
    }
  }
  return res;
}

linked_list linked_list::intersectionSet(const linked_list& right) {
  linked_list res;
  node* curr = res.head;
  for (node* p = head->next; p; p = p->next) {
    for (node* q = right.head->next; q; q = q->next) {
      if (p->data == q->data) {
        node* newNode = new node(p->data);
        curr->next = newNode;
        curr = curr->next;
        res.size++;
      }
    }
  }
  return res;
}

node* linked_list::find(DataType value) {
  node* p = head->next;
  while (p) {
    if (p->data == value) {
      return p;
    }
    p = p->next;
  }
  return nullptr;
}

bool linked_list::find(DataType value, node*& pre, node*& p) {
  pre = head;
  p = pre->next;
  while (p) {
    if (p->data == value) {
      return 1;
    }
    pre = pre->next;
    p = pre->next;
  }
  return 0;
}

void linked_list::add_front(DataType value) {
  node* newNode = new node(value);
  newNode->next = head->next;
  head->next = newNode;
  size++;
}

void linked_list::add_tail(DataType value) {
  node* p = head->next;
  while (p) {
    tail = p;
    p = p->next;
  }
  node* newNode = new node(value);
  tail->next = newNode;
  tail = newNode;
  size++;
}

void linked_list::add_pos_after(DataType value, node* pos) {
  if (pos == nullptr) {
    return;
  }
  node* newNode = new node(value);
  newNode->next = pos->next;
  pos->next = newNode;
  size++;
}

void linked_list::add_pos_before(DataType value, node* pos) {
  if (pos == nullptr) {
    return;
  }
  node* newNode = new node(value);
  node* pre = head;
  while (pre->next != pos) {
    pre = pre->next;
  }
  newNode->next = pos;
  pre->next = newNode;
  size++;
}

void linked_list::Delete(DataType value) {
  node* pre = head;
  for (node* p = head->next; p; pre = pre->next, p = p->next) {
    if (p->data == value) {
      pre->next = p->next;
      delete p;
      p = nullptr;
      size--;
      break;
    }
  }
}

void linked_list::delete_pos_after(node* pos) {
  if (pos == nullptr) {
    return;
  }
  node* p = pos->next;
  if (p == nullptr) {
    return;
  }
  pos->next = p->next;
  delete p;
  p = nullptr;
  size--;
}

void linked_list::delete_pos_before(node* pos) {
  if (pos == nullptr) {
    return;
  }
  node* pre = head;
  while (pre && pre->next->next != pos) {
    pre = pre->next;
  }
  if (pre == nullptr) {
    return;
  }
  node* p = pre->next;
  pre->next = p->next;
  //   p->next = nullptr;
  delete p;
  p = nullptr;
  size--;
}

void linked_list::delete_all(DataType value) {
  node* pre = head;
  node* p = head->next;
  while (p) {
    if (p->data == value) {
      pre->next = p->next;
      delete p;
      p = pre->next;
      size--;
    } else {
      pre = pre->next;
      p = pre->next;
    }
  }
}

void linked_list::delete_repeat() {
  for (node* p = head->next; p; p = p->next) {
    DataType value = p->data;
    node* pre = p;
    node* q = p->next;
    while (q) {
      if (q->data == value) {
        pre->next = q->next;
        delete q;
        q = pre->next;
        size--;
      } else {
        pre = pre->next;
        q = pre->next;
      }
    }
  }
}

void linked_list::reverse() {
  node* p = head->next;
  head->next = nullptr;
  while (p) {
    node* pre = p;
    p = p->next;
    pre->next = head->next;
    head->next = pre;
  }
}

void linked_list::sort() {
  for (node* p = head->next; p->next; p = p->next) {
    for (node* q = p->next; q; q = q->next) {
      if (p->data > q->data) {
        DataType tmp = q->data;
        q->data = p->data;
        p->data = tmp;
      }
    }
  }
}

void linked_list::display() {
  node* p = head->next;
  while (p->next) {
    std::cout << p->data << ",";
    p = p->next;
  }
  std::cout << p->data << std::endl;
}

linked_list::~linked_list() {
  node* p = head;
  node* nextNode;
  while (p) {
    nextNode = p->next;
    delete p;
    p = nextNode;
  }
  head = nullptr;
}

linked_list mergeSortedList(const linked_list& L1, const linked_list& L2) {
  linked_list l1 = L1;
  linked_list l2 = L2;
  linked_list res = l1 + l2;
  res.sort();
  return res;
}