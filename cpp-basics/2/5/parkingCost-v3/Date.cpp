#include "Date.hpp"

#include <iostream>
using namespace std;

// 闰年判断
bool isLeap(int year) {
  if (year % 4 == 0 && year % 100 != 0 || year % 400 == 0) {
    return true;
  }
  return false;
}

// 有31天的月份
bool is31day(int month) {
  if (month == 1 || month == 3 || month == 5 || month == 7 || month == 8 ||
      month == 10 || month == 12) {
    return true;
  }
  return false;
}

// 有30天的月份
bool is30day(int month) {
  if (month == 4 || month == 6 || month == 9 || month == 11) {
    return true;
  }
  return false;
}

void Date::show_date() { cout << year << "-" << month << "-" << day << " "; }

void Date::set_date() {
  do {
    cin >> year >> month >> day;
  } while (year < 0 || month <= 0 || month > 12 || day <= 0 ||
           (isLeap(year) && month == 2 && day > 29) ||
           (!isLeap(year) && month == 2 && day > 28) ||
           (is31day(month) && day > 31) || (is30day(month) && day > 30));
}

int Date::diff(Date& T) {
  // 这里的d用来存储天数差
  long d = normalize() - T.normalize();

  // 考虑年份差的影响
  int y = year - T.year;  // 计算年份差
  if (y > 0) {
    if (isLeap(T.year) && T.month < 2 ||
        isLeap(T.year) && T.month == 2 && T.day < 29 ||
        isLeap(year) && month > 2 || isLeap(year) && month == 2 && day == 29) {
      // 停车的年份是闰年且还未度过2.29这一天，或者结算的年份是闰年且已经度过了2.29这一天
      d += 366;
    } else {
      d += 365;
    }
  }

  return d;
}

long Date::normalize() {
  int num = 0;   // 每个月的天数
  long sum = 0;  // 总天数(从1月1日算起)

  // 计算除当前月份的前几个月份的总天数
  for (int i = 1; i < month; i++) {
    if (isLeap(year) && i == 2) {
      num = 29;
    } else if (!isLeap(year) && i == 2) {
      num = 28;
    }

    if (is31day(i)) {
      num = 31;
    } else if (is30day(i)) {
      num = 30;
    }
    sum += num;
  }
  sum += day;  // 算上当前月份的当前天数
  return sum;
}