#include <iostream>
using namespace std;

int main() {
  unsigned int a, b;
  while (cin >> a >> b) {
    while (b % a) {
      int c = b % a;
      b = a;
      a = c;
    }
    cout << a << endl;
  }
}