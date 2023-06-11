// #include "time.hpp"
#include <iostream>

#include "time.cpp"
using namespace std;

double parkingFee(double t);

int main() {
  time_clock arriveTime, leaveTime;
  double parkingTime, Fee;
  arriveTime.set_time();
  arriveTime.show_time();
  leaveTime.set_time();
  leaveTime.show_time();

  parkingTime = leaveTime.diff(arriveTime);
  Fee = parkingFee(parkingTime);
  cout << "收费" << Fee << endl;

  return 0;
}

double parkingFee(double t) { return 4 * t; }