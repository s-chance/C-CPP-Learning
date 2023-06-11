// C++ How to Program
// Debugging Problem (lion.cpp)

#include <iostream>

using std::cout;

#include "lion.hpp"

Lion::Lion(const int h, const int w) : Animal(h, w) {}  // 没有继承Animal类

void Lion::print() const {
  cout << "This animal is a lion\n";
}
