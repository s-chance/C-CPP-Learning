#ifndef TRUCK_HPP
#define TRUCK_HPP

#include <iostream>

#include "vehicle.hpp"
using std::string;

class Truck : public Vehicle {
 public:
  Truck(int d, int c, int t, string s, double l, int cargo = 0)
      : Vehicle(d, c, t, s, l), cargo(cargo) {}

  void F6();  // 输出货物信息
 private:
  int cargo;
};
#endif