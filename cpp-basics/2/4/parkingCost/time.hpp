class time_clock {
 public:
  void show_time();
  void set_time();
  double diff(time_clock& T);

 private:
  long normalize();
  int hour;
  int minute;
  int second;
};