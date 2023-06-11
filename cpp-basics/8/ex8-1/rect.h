#ifndef RECT_H
#define RECT_H
#include "point.h"
// Rect类的声明 rect.h
class Rect : public Point {
 public:
  Rect(float x = 0, float y = 0, float w = 0, float h = 0);  // 构造函数
  void setWidth(float);                                      // 设置宽度
  void setHeight(float);                                     // 设置高度
  float getWidth() const;                                    // 读取宽度
  float getHeight() const;                                   // 读取高度
  float area() const;  // 计算矩形面积
  friend ostream& operator<<(ostream&, const Rect&);

 private:
  float width;
  float height;
};
#endif