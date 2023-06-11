#ifndef _POSITION_HPP_
#define _POSITION_HPP_

class Position {
 private:
  double x;
  double y;

 public:
  Position(double x = 0, double y = 0);
  Position(const Position& p);  // 拷贝构造函数
  ~Position();

  void set(double x = 0, double y = 0);

  double getX() const;
  double getY() const;

  void show() const;  // 判断第几象限

  double slope() const;  // 计算经过源点到这个位置的直线的斜率

  double slope(Position p) const;  // 计算经过这个位置到其他点的直线的斜率

  void move(double m = 0, double n = 0);  // 按坐标轴平移位置
};
double Distance(Position);  // 计算到源点的距离

double Distance(Position, Position);  // 计算到其他点的距离
#endif
