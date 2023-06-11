class Date {
 public:
  void show_date();
  void set_date();
  int diff(Date& T);
  int get_month() { return this->month; }
  int get_year() { return this->year; }

  friend class Time;  // 让Time类可以访问Date的私有成员

 private:
  long normalize();
  int year;
  int month;
  int day;
};