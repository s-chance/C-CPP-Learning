#include <iostream>
using namespace std;

int main() {
  char str[50];
  while (cin.getline(str, 50)) {
    for (int i = 0; i < str[i]; i++) {
      if (str[i] >= 65 && str[i] <= 90) {
        cout << (char)(str[i] + 32);
      } else if (str[i] >= 97 && str[i] <= 122) {
        cout << (char)(str[i] - 32);
      } else {
        cout << str[i];
      }
    }
    cout << '\n';
  }
}