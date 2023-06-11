#include <cstdio>
#include <cstring>
#include <iostream>

#include "myString.cpp"
#include "myVector.hpp"
using namespace std;

int compare(const char* c1, const char* c2, int begin = -1, int len = -1) {
  if (begin >= 0 && len > 0) {
    string s1 = c1;
    string s2 = c2;
    s1 = s1.substr(begin, len);
    s2 = s2.substr(begin, len);
    return strcmp(s1.c_str(), s2.c_str());
  }
  return strcmp(c1, c2);
}

// void selectSort(myVector<myString>& arr) {
//   for (int i = 0; i < arr.get_size() - 1; i++) {
//     int index = i;
//     for (int j = i + 1; j < arr.get_size(); j++) {
//       if (compare(arr[index], arr[j]) < 0) {
//         index = j;
//       }
//     }
//     if (index != i) {
//       swap(arr[i], arr[index]);
//     }
//   }
// }

void selectSort(myVector<myString>& arr, int begin = -1, int end = -1) {
  for (int i = 0; i < arr.get_size() - 1; i++) {
    int index = i;
    for (int j = i + 1; j < arr.get_size(); j++) {
      if (compare(arr[index], arr[j], begin, end) < 0) {
        index = j;
      }
    }
    if (index != i) {
      swap(arr[i], arr[index]);
    }
  }
}

void print(myVector<myString> arr) {
  for (int i = 0; i < arr.get_size(); i++) {
    cout << arr[i] << " ";
  }
  cout << endl;
}

int main() {
  const int num = 6;
  char str[num][20] = {"azshajhsha", "azasasuays", "gyyyuuyyko",
                       "cnjkgdswre", "defgcvbfds", "slopamzfgh"};
  myVector<myString> arr(num);
  for (int i = 0; i < arr.get_size(); i++) {
    arr[i] = str[i];
  }
  cout << "原始顺序: ";
  print(arr);

  selectSort(arr);
  cout << "选择排序: ";
  print(arr);

  selectSort(arr, 1, 5);
  cout << "子串比较排序: ";
  print(arr);
}