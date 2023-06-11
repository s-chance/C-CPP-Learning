#include <iostream>
using namespace std;
const int CAPACITY = 1000;

template <typename T>
class myVector {
 public:
  // 构造系列
  myVector(unsigned n = 10,
           T value = T());  // 用指定值value初始化n个单元  ,n<=CAPACITY
  myVector(const myVector<T>& obj);  // 拷贝构造
  // 赋值重载
  myVector<T>& operator=(const myVector<T>& right);
  // 下标运算
  T& operator[](unsigned index);
  // 调整容量
  void set_size(unsigned newsize);  // 调整容量到newsize ,newsize<=CAPACITY
  // 获取容量
  int get_size() const;

  // 也可以用下面两个函数代替
  // void expand(unsigned delta);//调整容量到size+delta
  // void subtract(unsigned delta);//调整容量到size-delta
  myVector<T>
  operator-();  // 返回元素逆置存放的向量，即将原向量元素首尾交换的结果，注意原向量保持不变。

  void sort();  // 升序排序

  void display() const;  // 从0开始显示向量元素  ,以逗号分隔每个单元值
  myVector<T>
  operator++();  // 前置增量重载，将vector内每个单元值增加1，并返回修改后的vector
  myVector<T> operator++(
      int);  // 后置增量重载，将vector内每个单元值增加1，并返回修改前的vector

  friend myVector<T> operator+(const myVector<T>& left,
                               const myVector<T>& right) {
    myVector<T> temp(left.size + right.size);
    for (int i = 0; i < left.size; i++) {
      temp.data[i] = left.data[i];
    }
    for (int i = 0; i < right.size; i++) {
      temp.data[left.size + i] = right.data[i];
    }
    temp.sort();

    int k = 0;
    myVector<T> res(left.size + right.size);
    for (int i = 0; i < temp.size - 1; i++) {
      if (temp.data[i] != temp.data[i + 1]) {
        res.data[k] = temp.data[i];
        k++;
      }
    }
    res.data[k] = temp.data[temp.size - 1];
    res.set_size(k + 1);
    return res;
  }
  friend myVector<T> operator-(const myVector<T>& left,
                               const myVector<T>& right) {
    myVector<T> res(left.size);

    int k = 0;
    for (int i = 0; i < left.size; i++) {
      bool flag = true;
      for (int j = 0; j < right.size; j++) {
        if (left.data[i] == right.data[j]) {
          flag = false;
          break;
        }
      }
      if (flag) res.data[k++] = left.data[i];
    }
    res.set_size(k);
    return res;
  }

  // 输入输出流重载
  friend ostream& operator<<(ostream& out, const myVector<T>& vec);
  friend istream& operator>>(istream& in, myVector<T>& vec);

 private:
  T data[CAPACITY];
  int size;  // 有效单元个数
};

template <typename T>
myVector<T> operator+(const myVector<T>& left, const myVector<T>& right);
// 表示求复杂可以求left和right的并集, 并集元素个数不超过CAPACITY

template <typename T>
myVector<T> operator-(const myVector<T>& left, const myVector<T>& right);
// 表示求left和right的差集

template <typename T>
ostream& operator<<(
    ostream& out,
    const myVector<T>&
        vec);  // 输出流重载。从0开始显示向量元素，以逗号分隔每个单元值

template <typename T>
istream& operator>>(istream& in, myVector<T>& vec);  // 输入流重载

/* 实现部分*/

template <typename T>
myVector<T>::myVector(unsigned n, T value) {
  size = n;
  for (int i = 0; i < size; i++) {
    data[i] = value;
  }
}

template <typename T>
myVector<T>::myVector(const myVector<T>& obj) {
  for (int i = 0; i < obj.size; i++) {
    data[i] = obj.data[i];
  }
  size = obj.size;
}

template <typename T>
myVector<T>& myVector<T>::operator=(const myVector<T>& right) {
  for (int i = 0; i < right.size; i++) {
    data[i] = right.data[i];
  }
  size = right.size;
  return *this;
}

template <typename T>
T& myVector<T>::operator[](unsigned index) {
  return data[index];
}

template <typename T>
void myVector<T>::set_size(unsigned newsize) {
  if (newsize < 0) {
    newsize = 0;
  } else if (newsize > CAPACITY) {
    cout << "Out of CAPACITY!" << endl;
    return;
  }

  size = newsize;
}

template <typename T>
int myVector<T>::get_size() const {
  return size;
}

template <typename T>
myVector<T> myVector<T>::operator-() {
  myVector* obj = new myVector(*this);
  for (int i = 0; i < obj->size; i++) {
    obj->data[i] = data[size - 1 - i];
  }
  return *obj;
}

template <typename T>
void myVector<T>::sort() {
  for (int i = 1; i < size; i++) {
    T value = data[i];
    int j = i - 1;
    while ((j >= 0) && (data[j] > value)) {
      data[j + 1] = data[j];
      j--;
    }
    data[j + 1] = value;
  }
}

template <typename T>
void myVector<T>::display() const {
  for (int i = 0; i < size; i++) {
    cout << data[i];
    if (i != size - 1) cout << ",";
  }
  cout << endl;
}

template <typename T>
myVector<T> myVector<T>::operator++() {
  for (int i = 0; i < size; i++) {
    data[i] += 1;
  }
  return *this;
}

template <typename T>
myVector<T> myVector<T>::operator++(int) {
  myVector* obj = new myVector(*this);
  for (int i = 0; i < size; i++) {
    data[i] += 1;
  }
  return *obj;
}

template <typename T>
ostream& operator<<(ostream& out, const myVector<T>& vec) {
  for (int i = 0; i < vec.get_size(); i++) {
    cout << vec.data[i];
    if (i != vec.get_size() - 1) cout << ",";
  }
  cout << endl;
  return out;
}

template <typename T>
istream& operator>>(istream& in, myVector<T>& vec) {
  for (int i = 0; i < 10; i++) {
    in >> vec.data[i];
  }
  vec.set_size(10);
  return in;
}
