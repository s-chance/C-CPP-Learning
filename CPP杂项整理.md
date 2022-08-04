### CPP基本数据类型
| 类型名称 | 字节 | 范围 |
|:--:|:--:|:--:|
|char|1|-128到127|
|unsigned char|1|0到255|
|short|2|$-2^{15}$到$2^{15}-1$|
|unsigned short|2|0到$2^{16}-1$|
|int|4|$-2^{31}$到$2^{31}-1$|
|unsigned int|4|0到$2^{32}-1$|
|long|4|$-2^{31}$到$2^{31}-1$|
|unsigned long|4|0到$2^{32}-1$|
|long long|8|$-2^{63}$到$2^{63}-1$|
|unsigned long long|8|0到$2^{64}-1$|
|bool|1|false或true|

| 类型名称 | 字节 | 指数位 | 范围 |
|:--:|:--:|:--:| :--:|
|float|4|8|$-2^{2^{7}}$到$2^{2^{7}}$|
|double|8|11|$-2^{2^{10}}$到$2^{2^{10}}$|

补充:
以上表格只列出了常用的类型名称,其余名称的类型在字节和范围上和表格中的类型没有区别

- 与char等同的类型名称:__int8、signed char

- 与unsigned char等同的类型名称:unsigned __int8、unsigned char

- 与short等同的类型名称:__int16、
short int、singned short int

- 与unsigned short等同的类型名称:unsigned __int16、unsigned short int、unsingned short int

- 与int等同的类型名称:__int32、signed、singned int

- 与unsigned int等同的类型名称:unsigned __int32、unsigned、unsingned int

- 与long等同的类型名称:long int、singned long int

- 与unsigned long等同的类型名称:unsingned long int

- 与long long等同的类型名称:__int64

- 与unsingned long long等同的类型名称:unsingned __int64

<font color='red'>注意:long的字节在不同环境下可能是不一样的</font>  
测试代码
```cpp
#include <iostream>
using namespace std;
int main()
{
  cout << "char:\t\t\t" << sizeof(char) << endl;
  cout << "unsigned char:\t\t" << sizeof(unsigned char) << endl;
  cout << "short:\t\t\t" << sizeof(short) << endl;
  cout << "unsigned short:\t\t" << sizeof(unsigned short) << endl;
  cout << "int:\t\t\t" << sizeof(int) << endl;
  cout << "unsigned int:\t\t" << sizeof(unsigned int) << endl;
  cout << "long:\t\t\t" << sizeof(long) << endl;
  cout << "unsigned long:\t\t" << sizeof(unsigned long) << endl;
  cout << "long long:\t\t" << sizeof(long long) << endl;
  cout << "unsigned long long:\t" << sizeof(unsigned long long) << endl;
  cout << "bool:\t\t\t" << sizeof(bool) << endl;
  cout << "float:\t\t\t" << sizeof(float) << endl;
  cout << "double:\t\t\t" << sizeof(double) << endl;
  return 0;
}
```