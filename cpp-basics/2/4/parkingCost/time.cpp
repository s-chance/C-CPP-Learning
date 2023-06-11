#include "time.hpp"

#include <iostream>
using namespace std;
void time_clock::show_time() {
  cout << hour << ":" << minute << ":" << second << endl;
}

void time_clock::set_time() {
  do {
    cin >> hour >> minute >> second;

  } while (hour < 0 || hour > 24 || minute < 0 || minute > 59 || second < 0 ||
           second > 59);
}

double time_clock::diff(time_clock& T) {
  long d = normalize() - T.normalize() - 60;
  if (d < 0) {
    return 0;
  }
  int h = d / 60, m = d % 60;
  if (m < 15) {
    return h;
  }
  if (m >= 15 && m < 30) {
    return h + 0.5;
  }
  if (m >= 30 && m < 60) {
    return h + 1;
  }
  return 0;
}

long time_clock::normalize() { return hour * 60 + minute; }