#include <iostream>

#include "circle.h"
#include "cube.h"
#include "cylinder.h"
#include "point.h"
#include "rect.h"
#include "sphere.h"
#include "triangle.h"

// 测试主函数
int main() {
  Point point(3.5, 6.4), *p;
  Circle circle(4, 5, 6), *cir;
  Cylinder cylinder(5, 6, 8), *cyl;

  cout << point;
  cout << circle;
  cout << cylinder;

  p = &point;
  cir = &circle;
  cyl = &cylinder;
  cout << (*p);
  cout << (*cir);
  cout << (*cyl);

  //+++++++++++++++++++
  cout << cir->area() << endl;
  cir = &cylinder;
  cout << cir->area() << endl;
  //+++++++++++++++++++

  //   p = &circle;
  //   cout << p->area() << endl;
  //   p = &cylinder;
  //   cout << p->area() << endl;
  //   Point &p1 = circle;
  //   cout << p1.area() << endl;
  //   Point &p2 = cylinder;
  //   cout << p2.area() << endl;

  //   Rect rect(1, 2, 3, 4);
  //   Triangle triangle(1, 2, 3, 4, 5, 2);
  //   Sphere sphere(1, 2, 3);
  //   Cube cube(1, 2, 3, 4);

  //   cout << rect;
  //   cout << triangle;
  //   cout << sphere;
  //   cout << cube;

  Point &rp1 = point;
  rp1 = circle;
  rp1.display(cout);
  point.display(cout);

  Point &rp2 = circle;
  rp2.display(cout);

  return 0;
}
