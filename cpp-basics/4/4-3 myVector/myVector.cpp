#include "myVector.hpp"

#include <istream>
#include <ostream>

myVector::myVector(unsigned n, int value) {
  size = n;
  for (int i = 0; i < size; i++) {
    data[i] = value;
  }
}

myVector::myVector(const myVector& obj) {
  for (int i = 0; i < obj.size; i++) {
    data[i] = obj.data[i];
  }
  size = obj.size;
}

myVector& myVector::operator=(const myVector& right) {
  for (int i = 0; i < right.size; i++) {
    data[i] = right.data[i];
  }
  size = right.size;
  return *this;
}

int& myVector::operator[](unsigned index) { return data[index]; }

void myVector::set_size(unsigned newsize) {
  if (newsize < 0) {
    newsize = 0;
  } else if (newsize > CAPACITY) {
    cout << "Out of CAPACITY!" << endl;
    return;
  } else if (newsize > size) {
    // 当newsize大于size时，将多的部分初始化
    for (int i = size; i < newsize; i++) {
      data[i] = 0;
    }
  }
  size = newsize;
}

int myVector::get_size() const { return size; }

myVector myVector::operator-() {
  myVector* obj = new myVector(*this);
  for (int i = 0; i < obj->size; i++) {
    obj->data[i] = data[size - 1 - i];
  }
  return *obj;
}

void myVector::sort() {
  for (int i = 1; i < size; i++) {
    int value = data[i];
    int j = i - 1;
    while ((j >= 0) && (data[j] > value)) {
      data[j + 1] = data[j];
      j--;
    }
    data[j + 1] = value;
  }
}

void myVector::display() const {
  for (int i = 0; i < size; i++) {
    cout << data[i];
    if (i != size - 1) cout << ",";
  }
  cout << endl;
}

myVector myVector::operator++() {
  for (int i = 0; i < size; i++) {
    data[i] += 1;
  }
  return *this;
}

myVector myVector::operator++(int) {
  myVector* obj = new myVector(*this);
  for (int i = 0; i < size; i++) {
    data[i] += 1;
  }
  return *obj;
}

myVector operator+(const myVector& left, const myVector& right) {
  myVector temp(left.size + right.size);
  for (int i = 0; i < left.size; i++) {
    temp.data[i] = left.data[i];
  }
  for (int i = 0; i < right.size; i++) {
    temp.data[left.size + i] = right.data[i];
  }
  temp.sort();

  int k = 0;
  myVector res(left.size + right.size);
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

myVector operator-(const myVector& left, const myVector& right) {
  myVector res(left.size);
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

ostream& operator<<(ostream& out, const myVector& vec) {
  for (int i = 0; i < vec.get_size(); i++) {
    cout << vec.data[i];
    if (i != vec.get_size() - 1) cout << ",";
  }
  cout << endl;
  return out;
}

istream& operator>>(istream& in, myVector& vec) {
  for (int i = 0; i < 10; i++) {
    in >> vec.data[i];
  }
  vec.set_size(10);
  return in;
}