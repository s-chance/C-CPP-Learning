#include "cube.h"

#include <ostream>

// Cube类的实现 cube.cpp
Cube::Cube(float x, float y, float z, float l)
    : Point(x, y), z(z), length(l) {}  // 构造函数

void Cube::setLength(float l) {  // 设置边长
  length = l;
}

float Cube::getLength() const {  // 读取边长
  return length;
}

float Cube::area() const {  // 计算表面积
  return 6 * length * length;
}

float Cube::volume() const {  // 计算体积
  return length * length * length;
}

ostream& operator<<(ostream& output, const Cube& c) {
  output << "Cube: [" << c.x << "," << c.y << "," << c.z << "],l=" << c.length
         << ",area=" << c.area() << ",volume=" << c.volume() << endl;
  return output;
}