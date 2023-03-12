#include <iostream>
using namespace std;
int main() {
  char ch[200] = {'\0'};
  int n = 50;
  while (n--) {
    cin >> ch;
    for (int i = 0; i < 200; i++) {
      if (ch[i] == '0') {
        cout << '1';
      } else if (ch[i] == '1') {
        cout << '0';
      } else {
        cout << endl;
        break;
      }
    }
  }
}