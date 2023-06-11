#include <iostream>

#include "pool.cpp"

using namespace std;

int main() {
  const double zddj = 167.5;  // 走道单价
  const double wldj = 36.4;   // 围栏单价
  double r;                   // 池直径
  double c;                   // 走m ji道宽
  pool apool;
  for (int l = 1; l <= 5; l++) {
    cout << "建造第" << l << "号游泳池：";
    apool.build();
    cout << "第" << l << "号游泳池造价为："
         << (apool.rail_length() * wldj + apool.rail_area() * zddj) << "元"
         << endl;
  }
}