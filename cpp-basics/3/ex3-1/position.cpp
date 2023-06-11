#include "position.hpp"

#include <cmath>
#include <iostream>

using namespace std;

Position::Position(double x, double y) : x(x), y(y) {}

Position::Position(const Position& p) {
  x = p.x;
  y = p.y;
}

Position::~Position() {}

void Position::set(double x, double y) {
  this->x = x;
  this->y = y;
}

double Position::getX() const { return x; }

double Position::getY() const { return y; }

void Position::show() const {
  if (x > 0 && y > 0) {
    cout << "第一象限" << endl;
  } else if (x < 0 && y > 0) {
    cout << "第二象限" << endl;
  } else if (x < 0 && y < 0) {
    cout << "第三象限" << endl;
  } else if (x > 0 && y < 0) {
    cout << "第四象限" << endl;
  } else {
    cout << "不属于任何象限" << endl;
  }
}

double Distance(Position p) {
  return sqrt(pow(p.getX(), 2) + (pow(p.getY(), 2)));
}

double Distance(Position a, Position b) {
  return sqrt(pow((a.getX() - b.getX()), 2) + pow((a.getY() - b.getY()), 2));
}

double Position::slope() const { return y / x; }

double Position::slope(Position p) const {
  return (p.getY() - y) / (p.getX() - x);
}

void Position::move(double m, double n) {
  x += m;
  y += n;
}