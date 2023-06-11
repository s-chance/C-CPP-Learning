#include "myString.hpp"

#include <cstdio>
#include <cstring>
#include <ios>
#include <istream>
#include <limits>
#include <ostream>
#include <string>

myString::myString() : str(nullptr), size(0) {}

myString::myString(string s) {
  str = new char[s.length() + 1]();
  strcpy(str, s.c_str());
  size = s.length();
}

myString::myString(char* ch, int begin, int size) {
  str = new char[size]();
  for (int i = begin; i < begin + size; i++) {
    str[i - begin] = ch[i];
  }
  str[begin + size] = '\0';
  this->size = size;
}

myString::myString(int n, char ch) {
  str = new char[n]();
  for (int i = 0; i < n; i++) {
    str[i] = ch;
  }
  str[n] = '\0';
  size = n;
}

myString::myString(const myString& mystring) {
  str = new char[mystring.size]();
  for (int i = 0; i < mystring.size; i++) {
    str[i] = mystring.str[i];
  }
  size = mystring.size;
}

void myString::display() const {
  if (size == 0) {
    cout << "空串" << endl;
  }
  for (int i = 0; i < size; i++) {
    cout << str[i];
  }
  cout << endl;
}

void myString::input() {
  string s;
  getline(cin, s);
  str = new char[s.length() + 1]();
  strcpy(str, s.c_str());
  size = s.length();
}

int myString::len() const { return size; }

char& myString::operator[](unsigned index) { return str[index]; }

myString& myString::operator=(const myString& right) {
  if (*this == right) {
    return *this;
  } else {
    str = new char[right.size + 1];
    for (int i = 0; i < right.size; i++) {
      str[i] = right.str[i];
    }
    str[right.size] = '\0';
    size = right.size;
    return *this;
  }
}

myString& myString::operator=(const char* right) {
  int newsize = strlen(right);
  if (size != newsize) {
    delete[] str;
    size = newsize;
    str = new char[size + 1];
  }
  strcpy(str, right);
  return *this;
}

myString::~myString() { delete[] str; }

int operator==(const myString& a, const char* b) {
  for (int i = 0; i < a.len(); i++) {
    if (a.str[i] != b[i]) {
      return 0;
    }
  }
  if (b[a.len()] != '\0') {
    return 0;
  }
  return 1;
}

myString myString::operator++(int) {
  myString* obj = this;
  for (int i = 0; i < size; i++) {
    if (str[i] > 'z' || str[i] < 'A' || str[i] > 'Z' && str[i] < 'a') {
      // 非字母部分不做处理
      continue;
    }
    str[i]++;
    if (str[i] > 'z') {
      str[i] = 'a';
    } else if (str[i] < 'a' && str[i] > 'Z') {
      str[i] = 'A';
    }
  }
  return *obj;
}

myString::operator const char*() { return str; }

int operator==(const myString& a, const myString& b) {
  if (a.len() != b.len()) {
    return 0;
  }
  for (int i = 0; i < a.len(); i++) {
    if (a.str[i] != b.str[i]) {
      return 0;
    }
  }
  return 1;
}

int operator>(const myString& a, const myString& b) {
  for (int i = 0; i < a.len(); i++) {
    if (a.str[i] > b.str[i]) {
      return 1;
    }
    if (a.str[i] < b.str[i]) {
      return 0;
    }
  }
  return 0;
}

myString operator+(const myString& a, const char* b) {
  myString res;
  res.str = new char[a.len() + strlen(b) + 1]();
  for (int i = 0; i < a.len(); i++) {
    res.str[i] = a.str[i];
  }

  int i = a.len();
  while (b[i - a.len()]) {
    res.str[i] = b[i - a.len()];
    i++;
  }
  res[i] = '\0';
  res.size = i;
  return res;
}

myString operator+(const myString& a, const myString& b) {
  myString res;
  res.str = new char[a.len() + b.len() + 1]();
  for (int i = 0; i < a.len(); i++) {
    res.str[i] = a.str[i];
  }
  for (int i = 0; i < b.len(); i++) {
    res.str[a.len() + i] = b.str[i];
  }
  res.str[a.len() + b.len()] = '\0';
  res.size = a.len() + b.len();
  return res;
}

ostream& operator<<(ostream& out, const myString& mystring) {
  for (int i = 0; i < mystring.size; i++) {
    out << mystring.str[i];
  }
  //   out << endl;
  return out;
}

istream& operator>>(istream& in, myString& mystring) {
  string s;
  in >> s;
  mystring.str = new char[s.length() + 1];
  strcpy(mystring.str, s.c_str());
  mystring.size = s.length();
  return in;
}