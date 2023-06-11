#include <iostream>

#include "Time.cpp"

using namespace std;

double parkingFee(double t);

double parkingFee_2(double t);

int main() {
  Date arrive_date, leave_date;
  Time arrive_time, leave_time;

  double parkingTime, Fee;
  arrive_date.set_date();
  arrive_time.set_time();
  // 同步数据
  arrive_time.sync_date(arrive_date);

  arrive_date.show_date();
  arrive_time.show_time();

  leave_date.set_date();
  leave_time.set_time();
  // 同步数据
  leave_time.sync_date(leave_date);

  leave_date.show_date();
  leave_time.show_time();

  // 时分秒计算
  parkingTime = leave_time.diff(arrive_time);
  Fee = parkingFee(parkingTime);
  parkingTime = leave_date.diff(arrive_date);

  if (parkingTime) {
    // 年月日计算
    parkingTime = leave_date.diff(arrive_date);
    // 停车时间已经超过一天
    Fee = parkingFee_2(parkingTime);
    int begin_month = arrive_date.get_month();
    int end_month = leave_date.get_month();
    int begin_year = arrive_date.get_year();
    int end_year = leave_date.get_year();

    int d_month = end_month - begin_month;
    int d_year = end_year - begin_year;
    if (d_month != 0) {
      if (is31day(begin_month) && parkingTime > 31 ||
          is30day(begin_month) && parkingTime > 30 ||
          isLeap(begin_year) && begin_month == 2 && parkingTime > 29 ||
          !isLeap(begin_month) && begin_month == 2 && parkingTime > 28) {
        Fee = parkingFee_2(parkingTime) * 0.9;
      }
    }
    if (d_year != 0) {
      Fee = parkingFee_2(parkingTime) * 0.9;
      if (isLeap(begin_year) && parkingTime > 366 ||
          !isLeap(begin_year) && parkingTime > 365) {
        Fee = parkingFee_2(parkingTime) * 0.8;
      }
    }
  }
  cout << "收费" << Fee << endl;

  return 0;
}

double parkingFee(double t) { return 4 * t; }

double parkingFee_2(double t) { return 30 * t; }