#include <iostream>
using namespace std;
class A {
 public:
  A(int x = 1) : ax(x) { cout << "A(int=1):" << ax << endl; }
  ~A() { cout << "~A():" << ax << endl; }

 protected:
  int ax;
};
class B : virtual public A {
 public:
  B(int xa, int xb) : A(xa), bx(xb) {
    cout << "B(int,int):ax=" << ax << ",bx=" << bx << endl;
  }
  ~B() { cout << "~B():" << endl; }

 protected:
  int bx;
};
class C : virtual public A {
 public:
  C(int xa, int xc) : cx(xc) {
    cout << "C(int,int):ax=" << ax << ",cx=" << cx << endl;
  }
  ~C() { cout << "~C():" << endl; }

 protected:
  int cx;
};
class D : public B, public C {
 public:
  D(int xa, int xb, int xc, int xd)
      : C(xa, xc),
        B(xa, xb),
        A(xa) {  // 没有定义虚基类时，这里的A(xa)去掉；有虚基类定义时这里的A(xa)也是可写可不写
    dx = xd;
    cout << "D(int,int):ax=" << B::ax << ",bx=" << bx << ",cx=" << cx
         << ",dx=" << dx << endl;
  }
  ~D() { cout << "~D():" << endl; }

 protected:
  int dx;
};

int main() {
  D obj(2, 3, 4, 5);  // 比较去掉virtual后的构造和析构的执行顺序

  return 0;
}