#include <iostream>
using namespace std;

int main() {
  long long n;
  while (cin >> n) {
    if (n == 0) break;
    if (n % 7 == 0) {
      cout << "Yes" << endl;
      continue;
    }
    while (n) {
      if (n % 10 == 7) {
        cout << "Yes" << endl;
        break;
      } else {
        n /= 10;
        if (n == 0) cout << "No" << endl;
      }
    }
  }
}