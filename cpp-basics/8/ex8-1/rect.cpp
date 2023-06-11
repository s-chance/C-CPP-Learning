#include "rect.h"

#include <ostream>

// Rect类的实现 rect.cpp
Rect::Rect(float a, float b, float w, float h)
    : Point(a, b), width(w), height(h) {}  // 构造函数

void Rect::setWidth(float w) {  // 设置宽度
  width = w;
}

void Rect::setHeight(float h) {  // 设置高度
  height = h;
}

float Rect::getWidth() const {  // 读取宽度
  return width;
}

float Rect::getHeight() const {  // 读取高度
  return height;
}

float Rect::area() const {  // 计算矩形面积
  return width * height;
}

ostream& operator<<(ostream& output, const Rect& r) {
  output << "Rect: Center=[" << r.x << "," << r.y << "],w=" << r.width
         << ",h=" << r.height << "\n area=" << r.area() << endl;
  return output;
}