#include <iostream>
using namespace std;

int main() {
  int n, m;

  cin >> n;
  while (n--) {
    cin >> m;
    if (m == 1) {
      cout << "yes" << endl;
      break;
    }
    int a[101] = {0};
    int min = -1;
    int max = -1;
    int gap = 0;
    for (int i = 0; i < m; i++) {
      cin >> a[i];
      if (min == -1 || a[i] < min) {
        min = a[i];
      }
      if (max == -1 || a[i] > max) {
        max = a[i];
      }
    }
    bool flag = true;
    gap = (max - min) / (m - 1);
    for (int i = 0; i < m - 1; i++) {
      int index = i;
      for (int j = i + 1; j < m; j++) {
        if (a[index] > a[j]) {
          index = j;
        }
      }
      if (index != i) {
        int t = a[i];
        a[i] = a[index];
        a[index] = t;
      }
      if (i > 0 && a[i] != a[i - 1] + gap) {
        flag = false;
        break;
      }
    }
    if (flag) {
      cout << "yes" << endl;
    } else {
      cout << "no" << endl;
    }
  }
}