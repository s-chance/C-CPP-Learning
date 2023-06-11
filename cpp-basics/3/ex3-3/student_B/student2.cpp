// student2.cpp  在此给出student2的实现
#include "student2.h"

Student::Student() { name = new char[20]; }

Student::Student(const char *n) { name = (char *)n; }

Student::Student(const Student &other) { name = other.name; }

void Student::operator=(const Student &right) { name = right.name; }

Student::~Student() {}

char *Student::GetName() {  // 获取名字
  return name;
}
void Student::ChangeName(const char *n) {  // 改名
  name = (char *)n;
}