/*
Измените данную программу, добавляя только операции разрешения области видимости
:: так, чтобы было напечатано число 16.
#include <iostream>

using namespace std;
int t = 1;
namespace A{ //int t = 14;
    namespace B{ int t = 6; }
    int t = 1;
}

struct X{ int t;
    struct Y{ int t; Y() {t = 6;}} y1;
    X() {t = 9;}
    public:
        int h(){ {int t = 14;}
        return _t + _t + _t;}
    };

int main(){
    X b;
    cout << b.h() << endl;
    return 0;
}

*/

#include <iostream>

using namespace std;
int t = 1;
namespace A { // int t = 14;
namespace B {
int t = 6;
}
int t = 1;
} // namespace A

struct X {
  int t;
  struct Y {
    int t;
    Y() { t = 6; }
  } y1;
  X() { t = 9; }

public:
  int h() {
    { int t = 14; }
    return ::t + A::B::t + t;
  };
};
int main() {
  X b;
  cout << b.h() << endl;
  return 0;
}
