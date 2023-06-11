#include "triangle.h"

#include <ostream>

// Triangle类的实现 triangle.cpp
Triangle::Triangle(float x1, float y1, float x2, float y2, float x3, float y3)
    : Point(x1, y1), x2(x2), y2(y2), x3(x3), y3(y3) {}

void Triangle::setPoint(float a, float b, float c, float d, float e,
                        float f) {  // 设置坐标值
  x = a;
  y = b;
  x2 = c;
  y2 = d;
  x3 = e;
  y3 = f;
}

float Triangle::getArea() const {  // 读取面积
  return 0.5 * abs((x - x3) * (y2 - y3) - (x2 - x3) * (y - y3));
}

ostream& operator<<(ostream& output, const Triangle& t) {
  output << "Triangle: (" << t.x << "," << t.y << "),(" << t.x2 << "," << t.y2
         << "),(" << t.x3 << "," << t.y3 << ")\n area=" << t.getArea() << endl;
  return output;
}