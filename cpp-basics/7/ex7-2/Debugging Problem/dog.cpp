// C++ How to Program
// Debugging Problem (dog.cpp)

#include <cstring>
#include <iostream>

#include "animal.hpp"

using std::string;

using std::cout;
using std::endl;

#include "dog.hpp"

Dog::Dog(const int h, const int w, const char* n) : Animal(h, w) {
  strcpy(name, n);
}

void Dog::setName(const char* n) { strcpy(name, n); }

void Dog::Print() const {
  cout << "The dog is named: " << name << endl;
  print();
}

Animal& Dog::operator=(const Animal& right) {
  setHeight(right.getHeight());
  setWeight(right.getWeight());
  setName(right.getName());
  return *this;
}
