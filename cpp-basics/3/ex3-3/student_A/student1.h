// student1.h
class Student {
 public:
  Student();  // 考虑这里为什么不缺省无参构造?
  // 因为已经存在了有参构造，系统不会再自动提供默认的无参构造
  Student(const char *n);
  // Student(const Student & other);
  // Student& operator=(const Student& right);
  //~Student( );
  char *GetName();                 // 获取名字
  void ChangeName(const char *n);  // 改名
 private:
  char name[20];
};
