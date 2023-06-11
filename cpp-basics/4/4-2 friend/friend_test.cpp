#include "friend_test.h"
Clock::Clock(int h, int m, int s)  // 类clock的构造函数
{
  hour = h;
  minute = m;
  second = s;
}
void Clock::display(const Date &d)  // display的作用是输出年、月、日和时、分、秒
{
  cout << d.month << "/" << d.day << "/" << d.year
       << endl;  // 引用Date类对象中的私有数据
  cout << hour << ":" << minute << ":" << second
       << endl;  // 引用本类对象中的私有数据
}
// void Clock::display(const Date *d) {
//   cout << d->month << "/" << d->day << "/" << d->year
//        << endl;  // 访问公有数据成员
//   cout << hour << ":" << minute << ":" << second
//        << endl;  // 引用本类对象中的私有数据
// }
void Clock::display(const Date *d) {
  cout << d->getMonth() << "/" << d->getDay() << "/" << d->getYear()
       << endl;  // 访问公有数据成员
  cout << hour << ":" << minute << ":" << second
       << endl;  // 引用本类对象中的私有数据
}
Date::Date(int m, int d, int y)  // 类Date的构造函数
{
  month = m;
  day = d;
  year = y;
}

// 公有接口部分
int Date::getMonth() const { return this->month; }

int Date::getDay() const { return this->day; }

int Date::getYear() const { return this->year; }