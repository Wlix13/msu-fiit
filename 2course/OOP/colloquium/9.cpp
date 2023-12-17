/*
Поставить this там, где он ставится неявно.
class mstr { int x, y,z;
public: mstr (int n, int m, int h);
int F() {int d; d = x; return d * y; }
void G(); };
void mstr::G() {int a; a = F(); cout << a << x << endl;}
mstr::mstr (int n, int m,int h) {x = n; y = m; z = h;}
*/

#include <iostream>

using namespace std;
class mstr {
  int x, y, z;

public:
  mstr(int n, int m, int h);
  int F() {
    int d;
    d = x;
    return d * y;
  }
  void G();
};
void mstr::G() {
  int a;
  a = F();
  cout << a << " " << x << endl;
}

mstr::mstr(int n, int m, int h) {
  this->x = n;
  this->y = m;
  this->z = h;
}

int main() {
  mstr a(1, 2, 3);
  a.G();
  return 0;
}