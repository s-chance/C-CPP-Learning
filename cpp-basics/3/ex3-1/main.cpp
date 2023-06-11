#include <iostream>

#include "position.hpp"
using namespace std;

int main() {
  Position a;                             // 默认坐标位置为原点
  Position b(4, 5), c(b), d(0, 0), e(1);  // b的位置为x轴值4，y轴值5
  cout << "a(0,0):";
  a.show();
  a.set(5, 15);
  cout << "a(5,15):";
  a.show();
  cout << "b(4,5):";
  b.show();
  b.set(-4.5, 6.7);
  cout << "b(-4.5,6.7):";
  b.show();
  cout << "c(4,5):";
  c.show();
  c.set(-10, -100);
  cout << "c(-10,-100):";
  c.show();
  cout << "d(0,0):";
  d.show();
  d.set(20.5, 5.5);
  cout << "d(20.5,5.5):";
  d.show();
  cout << "e(1,0):";
  e.show();
  e.set();  // 默认为原点
  cout << "e(0,0):";
  e.show();
  cout << Distance(a, b) << endl;
  cout << Distance(c) << endl;  // 默认求与原点的距离
  cout << a.slope() << endl;    // 与原点构成直线的斜率
  cout << a.slope(d) << endl;   // 与d构成直线的斜率
  a.move(3);                    // 沿x轴平移
  cout << "a(8,15):";
  a.show();
  b.move(-4, 5);
  cout << "b(-8.5,11.7):";
  b.show();
  c.move(0, 6);  // 沿y轴平移
  cout << "c(-10,-94):";
  c.show();
  return 0;
}