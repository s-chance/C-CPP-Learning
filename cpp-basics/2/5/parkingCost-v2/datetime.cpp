#include "datetime.hpp"

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

void datetime::show_time() {
  cout << year << "-" << month << "-" << day << " " << hour << ":" << minute
       << ":" << second << endl;
}

void datetime::set_time() {
  do {
    cin >> year >> month >> day >> hour >> minute >> second;

  } while (year < 0 || month <= 0 || month > 12 || day <= 0 ||
           (isLeap(year) && month == 2 && day > 29) ||
           (!isLeap(year) && month == 2 && day > 28) ||
           (is31day(month) && day > 31) || (is30day(month) && day > 30) ||
           hour < 0 || hour > 24 || minute < 0 || minute > 59 || second < 0 ||
           second > 59);
}

// 计算不超过一天的停车费
double datetime::diff(datetime& T) {
  long d = normalize() - T.normalize();
  if (d <= 0) {
    // 考虑天数差的影响
    int dd = day - T.day;
    if (dd <= 0) {
      // 考虑年份差的影响
      int y = year - T.year;
      if (y > 0) {
        // 将年转化天数
        if (isLeap(T.year) && T.month < 2 ||
            isLeap(T.year) && T.month == 2 && T.day < 29 ||
            isLeap(year) && month > 2 ||
            isLeap(year) && month == 2 && day == 29) {
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

// 计算超过一天的停车费
int datetime::diff_ymd(datetime& T) {
  // 这里的d用来存储天数差
  long d = normalize_ymd() - T.normalize_ymd();

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

long datetime::normalize() { return hour * 60 + minute; }

long datetime::normalize_ymd() {
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