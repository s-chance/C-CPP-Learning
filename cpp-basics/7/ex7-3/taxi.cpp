#include "taxi.hpp"

void Taxi::F6() {
  if (passenger == 0) {
    cout << "The taxi has no passengers." << endl;
  } else {
    cout << "The taxi has " << passenger << " passengers.";
  }
}