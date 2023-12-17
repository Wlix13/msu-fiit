/*
Задача 1.
Добавьте в программу необходимое описание так, чтобы в ней не было ошибок.
int main(){X::x1 = 7; const X ob;
           cout << ob.x2 * ob.g() << endl; return 0; }
*/

#include <iostream>

using namespace std;

class X {
public:
  static int x1; // static - для того, чтобы можно было обращаться к переменной
                 // класса без создания объекта
  int x2;
  int g() const { // const - потому что в main вызывается метод у константного
                  // объекта
    return x1;
  }

  X() { // конструктор по умолчанию
    x2 = 5;
  }
};

int X::x1 = 0; // инициализация статической переменной int

int main() {
  X::x1 = 7;
  const X ob;
  cout << ob.x2 * ob.g() << endl;
  return 0;
}