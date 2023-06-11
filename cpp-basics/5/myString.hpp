#include <iostream>
#include <istream>
#include <ostream>
#include <string>
using namespace std;
class myString {
 public:
  // 根据测试程序写构造函数原型
  myString();
  myString(string str);
  myString(char* ch, int begin, int end);
  myString(int n, char ch);
  myString(const myString& mystring);

  void display() const;  // 显示字符串
  void input();          // 输入字符串
  int len() const;       // 求字符串长

  // 补充下标重载运算
  char& operator[](unsigned index);
  // 补充赋值重载运算
  myString& operator=(const myString& right);
  myString& operator=(const char* right);
  // 补充析构函数
  ~myString();

  // 增量操作，将串内的每个字母循环调整为其后面的字母
  myString operator++(int);
  // 类型转换
  operator const char*();

  friend int operator==(const myString& a, const char* b);
  friend int operator==(const myString& a, const myString& b);
  friend int operator>(const myString& a, const myString& b);

  friend myString operator+(const myString& a, const char* b);
  friend myString operator+(const myString& a, const myString& b);

  friend ostream& operator<<(ostream& out, const myString& mystring);
  friend istream& operator>>(istream& in, myString& mystring);


 private:
  char* str;
  int size;
};

int operator==(const myString& a, const char* b);      // 字符串等于比较
int operator==(const myString& a, const myString& b);  // 重载
int operator>(const myString& a, const myString& b);   // 字符串大于比较
myString operator+(const myString& a, const char* b);  // 字符串拼接
myString operator+(const myString& a, const myString& b);  // 重载

// 考虑为myString添加输入输出流重载
ostream& operator<<(ostream& out, const myString& mystring);
istream& operator>>(istream& in, myString& mystring);