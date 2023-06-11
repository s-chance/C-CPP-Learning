#include <algorithm>
#include <fstream>
#include <iostream>
using namespace std;

int *fileIn(string fname, int n) {
  ifstream infile(fname, ios::in);
  if (!infile.is_open()) {
    cerr << "infile open error" << endl;
    return nullptr;
  }

  int *arr = new int[n];
  for (int i = 0; i < n; i++) {
    infile >> arr[i];
  }
  infile.close();
  return arr;
}

bool fileOut(string fname, int *arr, int n) {
  ofstream outfile(fname, ios::out);
  if (!outfile.is_open()) {
    cerr << "outfile open error" << endl;
    return false;
  }
  for (int i = 0; i < n; i++) {
    cout << arr[i] << " ";
    outfile << arr[i] << " ";
  }
  outfile.close();
  return true;
}

int main() {
  string fname = "./data1.txt";
  int n = 10;
  int *a = fileIn(fname, n);
  fname = "./data2.txt";
  int *b = fileIn(fname, n);

  int size = 20;
  int *c = new int[size];
  for (int i = 0; i < size; i++) {
    if (i < n) {
      c[i] = a[i];
    } else {
      c[i] = b[i - n];
    }
  }
  sort(&c[0], &c[size]);
  fname = "./data3.txt";
  fileOut(fname, c, size);
  delete[] a;
  delete[] b;
  delete[] c;
}