#ifndef VEHICLE_HPP
#define VEHICLE_HPP

#include <iostream>
using namespace std;

class Vehicle {
 public:
  Vehicle(int d, int c, int t, string s, double l)
      : doors(d), cylinders(c), type(t), color(s), level(l) {}
  void F1();  // 输出doors的数量
  void F2();  // 输出cylinders的数量
  void F3();  // 输出Transmission type
  void F4();  // 输出color
  void F5();  // 输出Fuel level
 private:
  int doors;
  int cylinders;
  int type;
  string color;
  double level;
};
#endif