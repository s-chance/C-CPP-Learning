#include <iostream>
using namespace std;

int main() {
  int m, n;
  string str;
  while (cin >> m >> n && m != 0 && n != 0) {
    int res = 0;
    for (int i = 0; i < m; i++) {
      cin >> str;
      for (int j = 0; j < n; j++) {
        if (str[j] == '*') {
          res++;
        }
      }
    }
    cout << res << endl;
  }
}