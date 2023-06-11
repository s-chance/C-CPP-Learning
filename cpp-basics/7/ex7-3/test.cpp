#include "taxi.hpp"
#include "truck.hpp"
#include "vehicle.hpp"

int main() {
  cout << "Vehicle" << endl;
  Vehicle vehicle(2, 6, 3, "blue", 14.6);
  vehicle.F1();
  vehicle.F2();
  vehicle.F3();
  vehicle.F4();
  vehicle.F5();

  cout << "Taxi" << endl;
  Taxi taxi(4, 6, 5, "yellow", 3.3, 0);
  taxi.F1();
  taxi.F2();
  taxi.F3();
  taxi.F4();
  taxi.F5();
  taxi.F6();

  cout << "Truck" << endl;
  Truck truck(2, 16, 8, "black", 7.54, 1);
  truck.F1();
  truck.F2();
  truck.F3();
  truck.F4();
  truck.F5();
  truck.F6();
}