#define pi 3.14
#include "pool.hpp"

#include <iostream>

using namespace std;

inline void pool::build() { cin >> radius >> c; }

inline double pool::rail_area() {
  // return pi * ((radius + c) * (radius + c) - radius * radius);
  return cir_area(radius + c) - cir_area(radius);
}

inline double pool::rail_length() { return 2 * pi * radius; }

inline double pool::cir_area(double rc) { return pi * rc * rc; }