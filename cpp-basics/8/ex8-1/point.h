#ifndef POINT_H
#define POINT_H
#include <iostream>
#include <ostream>
#include "shap.h"
using namespace std;
// Point类的声明 point.h
class Point:public Shape {
 public:
  Point(float x = 0, float y = 0);  // 有默认参数的构造函数
  void setPoint(float, float);      // 设置坐标值
  float getX() const { return x; }  // 读x坐标
  float getY() const { return y; }  // 读y坐标
  virtual float area() const { return 0; }
  virtual void display(ostream& out) const;            // 输出点的坐标
//   friend ostream& operator<<(ostream&, const Point&);  // 重载输出
 protected:                                            // 受保护成员
  float x, y;
};
ostream& operator<<(ostream& output, const Point& p);
#endif
