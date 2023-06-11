#include <iostream>

#include "datetime.cpp"
using namespace std;

double parkingFee(double t);

double parkingFee_2(double t);

int main() {
  datetime arriveTime, leaveTime;
  double parkingTime, Fee;
  arriveTime.set_time();
  arriveTime.show_time();
  leaveTime.set_time();
  leaveTime.show_time();

  // 时分秒计算
  parkingTime = leaveTime.diff(arriveTime);
  Fee = parkingFee(parkingTime);
  parkingTime = leaveTime.diff_ymd(arriveTime);

  if (parkingTime) {
    // 年月日计算
    parkingTime = leaveTime.diff_ymd(arriveTime);
    // 停车时间已经超过一天
    Fee = parkingFee_2(parkingTime);
    int begin_month = arriveTime.get_month();
    int end_month = leaveTime.get_month();
    int begin_year = arriveTime.get_year();
    int end_year = leaveTime.get_year();

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