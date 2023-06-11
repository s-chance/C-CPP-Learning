// #include "Date.hpp"
#include "Date.cpp"

class Time {
 public:
  void show_time();
  void set_time();
  void sync_date(Date& D) { date = D; }
  double diff(Time& T);

  friend class Date;  // 让Date类可以访问Time类的私有成员

  int& get_day() { return date.day; }
  int& get_month() { return date.month; }
  int& get_year() { return date.year; }

 private:
  long normalize();
  int hour;
  int minute;
  int second;
  Date date;
};