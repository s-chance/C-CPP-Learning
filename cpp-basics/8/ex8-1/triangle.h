#ifndef TRIANGLE_H
#define TRIANGLE_H
#include "point.h"
// Triangle类的声明 triangle.h
class Triangle : public Point {
 public:
  Triangle(float x1 = 0, float y1 = 0, float x2 = 0, float y2 = 0, float x3 = 0,
           float y3 = 0);                                   // 构造函数
  void setPoint(float, float, float, float, float, float);  // 设置坐标值
  float getArea() const;                                    // 读取面积
  friend ostream& operator<<(ostream&, const Triangle&);    // 重载输出
 protected:
  float x2, y2, x3, y3;
};
#endif