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
### CPP访问私有(private)成员变量的常用方法
1. 通过公共函数访问私有成员变量
2. 通过指针访问私有成员变量
3. 通过引用传参访问私有成员变量
### CPP创建类的数组
当创建类类型的数组时，没有被初始化的成员会调用类的默认构造函数，其他的构造函数不可能、也不可以被调用  
故，当一个类要当做数组的元素类型时，类必须有默认构造函数！否则，数组必须每个元素都显式地用指定的构造函数初始化！
### CPP中struct和class的区别
C++中的struct和class基本是通用的，唯有几个细节不同：
- 使用class时，类中的成员默认都是private属性的；而使用struct时，结构体中的成员默认都是public属性
- class继承默认是private继承，而struct继承默认是public继承
- class可以使用模板，而struct不能
### exit、abort、return终止程序方法的区别
- exit(): 调用时, 进行绝大部分清理工作, 但不会销毁局部对象, 没有stack unwinding
清理工作主要包括: 销毁所有static和global对象，清空所有缓冲区，关闭所有I／O通道
- abort(): 调用时, 不进行任何清理工作, 直接终止程序
- return: 调用时, 进行stack unwinding, 调用局部对象析构函数清理局部对象。如果在main中, 则之后再交由系统调用exit()
总结: return返回可析构main或函数中的局部变量, exit返回可析构全局变量(对象), abort则不对任何变量进行析构
故使用return更能避免内存泄漏