// 在main函数所在的文件中包含头文件header1.h:
#include <iostream>

#include "example3_header1.h"
#include "example3_header2.h"

// using namespace stud1;
using namespace stud2;

// 注意要用双引号，因为文件一般是放在用户目录中的
using namespace std;
int main() {
  Student stud1(101, "Wang", 18);  // 定义类对象stud1
  stud1.get_data();
  cout << fun(5, 3) << endl;
  return 0;
}