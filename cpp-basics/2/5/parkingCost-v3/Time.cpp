#include "Time.hpp"

#include <iostream>
using namespace std;

void Time::show_time() {
  cout << hour << ":" << minute << ":" << second << endl;
}

void Time::set_time() {
  do {
    cin >> hour >> minute >> second;

  } while (hour < 0 || hour > 24 || minute < 0 || minute > 59 || second < 0 ||
           second > 59);
}

double Time::diff(Time& T) {
  long d = normalize() - T.normalize();
  if (d <= 0) {
    // 考虑天数差的影响
    int& day = get_day();
    int& tday = T.get_day();
    int dd = day - tday;
    if (dd <= 0) {
      // 考虑年份差的影响
      int& year = get_year();
      int& tyear = T.get_year();
      int y = get_year() - T.get_year();
      if (y > 0) {
        // 将年转化天数
        if (isLeap(tyear) && T.get_month() < 2 ||
            isLeap(tyear) && T.get_month() == 2 && tday < 29 ||
            isLeap(year) && get_month() > 2 ||
            isLeap(year) && get_month() == 2 && day == 29) {
          day += 366;
        } else {
          day += 365;
        }
        year--;    // 年份减去一年，因为这一年不足365或366天
        return 0;  // 存在年份差，直接返回
      }
    }

    if (dd == 1) {
      // 天数差正好一天，加上 24 * 60 分钟
      d += (24 * 60);
      day--;  // 天数减去一天，因为不足24小时
    } else {
      // 天数差不止一天，使用其他计算方法
      day--;  // 天数减去一天，因为不足24小时
      return 0;
    }
  }

  d -= 60;  // 减去不收费的时间部分
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

long Time::normalize() { return hour * 60 + minute; }
