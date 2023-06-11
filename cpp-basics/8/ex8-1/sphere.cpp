#include "sphere.h"

#include <ostream>

// Sphere类的实现 sphere.cpp
Sphere::Sphere(float a, float b, float r) : Circle(a, b, r) {}

float Sphere::area() const {  // 计算球表面积
  return 4 * 3.14159 * radius * radius;
}

float Sphere::volume() const {  // 计算球体积
  return 4.0 / 3.0 * 3.14159 * radius * radius * radius;
}

ostream& operator<<(ostream& output, const Sphere& s) {
  output << "Sphere: Center=[" << s.x << "," << s.y << "],r=" << s.radius
         << "\n area=" << s.area() << ",volume=" << s.volume() << endl;
  return output;
}