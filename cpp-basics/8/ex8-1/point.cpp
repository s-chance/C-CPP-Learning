// Point类的实现 point.cpp
#include "point.h"

Point::Point(float a, float b) {  // 对x,y初始化
  x = a;
  y = b;
}

// 设置x和y的坐标值
void Point::setPoint(float a, float b) {  // 为x,y赋新值
  x = a;
  y = b;
}

void Point::display(ostream& out) const {  // 输出点的坐标
  out << "Point:" << x << "," << y << endl;
}

// 重载输出运算符
ostream& operator<<(ostream& output, const Point& p) {
  //   output << "[" << p.x << " " << p.y << "]" << endl;
  p.display(output);  // 调用Point类的display函数
  return output;
}
