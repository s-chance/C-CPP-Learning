#ifndef TAXI_HPP
#define TAXI_HPP

#include <iostream>

#include "vehicle.hpp"
using std::string;

class Taxi : public Vehicle {
 public:
  Taxi(int d, int c, int t, string s, double l, int passenger = 0)
      : Vehicle(d, c, t, s, l), passenger(passenger) {}

  void F6();  // 输出载客信息
 private:
  int passenger;
};
#endif