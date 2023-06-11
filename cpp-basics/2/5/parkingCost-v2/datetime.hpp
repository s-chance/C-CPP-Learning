class datetime {
 public:
  void show_time();
  void set_time();
  double diff(datetime& T);
  int diff_ymd(datetime& T);

  int get_month() { return this->month; }
  int get_year() { return this->year; }

 private:
  long normalize();
  int hour;
  int minute;
  int second;

  long normalize_ymd();
  int year;
  int month;
  int day;
};