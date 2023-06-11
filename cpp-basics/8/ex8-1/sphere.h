#ifndef SPHERE_H
#define SPHERE_H
#include "circle.h"
// Sphere类的声明 sphere.h
class Sphere : public Circle {
 public:
  Sphere(float x = 0, float y = 0, float r = 0);  // 构造函数
  float area() const;                             // 计算球表面积
  float volume() const;                           // 计算球体积
  friend ostream& operator<<(ostream&, const Sphere&);
};
#endif