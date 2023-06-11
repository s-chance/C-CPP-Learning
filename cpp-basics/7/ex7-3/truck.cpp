#include "truck.hpp"

void Truck::F6() {
  if (cargo == 0) {
    cout << "The truck is no carrying." << endl;
  } else {
    cout << "The truck is carrying." << endl;
  }
}