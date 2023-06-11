#include <cstdlib>
#include <fstream>
#include <iostream>
using namespace std;

int *randomData(int n) {
  int *arr = new int[10];
  for (int i = 0; i < n; i++) {
    arr[i] = rand() % 100;
  }
  return arr;
}

bool fileOperator(string fname, int *arr, int n) {
  ofstream outfile(fname, ios::out);
  if (!outfile.is_open()) {
    cerr << "open error" << endl;
    return false;
  }
  for (int i = 0; i < n; i++) {
    outfile << arr[i] << " ";
  }
  outfile.close();
  return true;
}

int main() {
  srand(time(0));
  string fname = "./data1.txt";
  int *a = randomData(10);
  fileOperator(fname, a, 10);
  fname = "./data2.txt";
  int *b = randomData(10);
  fileOperator(fname, b, 10);
}