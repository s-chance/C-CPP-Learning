#ifndef CUBE_H
#define CUBE_H
#include "point.h"
// Cube类的声明 cube.h
class Cube : public Point {
 public:
  Cube(float x = 0, float y = 0, float z = 0, float l = 0);  // 构造函数
  void setLength(float);                                     // 设置边长
  float getLength() const;                                   // 读取边长
  float area() const;                                        // 计算表面积
  float volume() const;                                      // 计算体积
  friend ostream& operator<<(ostream&, const Cube&);

 protected:
  float z;
  float length;
};
#endif