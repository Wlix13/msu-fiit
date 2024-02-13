/*
Написать две перегруженные функции fk и класс А (в нем не должно быть
конструктора преобразования) так, чтобы следующие вызовы отработали успешно.
... A ob: short x;

fk (ob, 7); // печатается сообщение "111"
fk (ob, 3.4); // печатается сообщение "22"
fk (x, 7); // печатается сообщение "111"
fk (2.4f, 7.0); // печатается сообщение "22"
fk (4, 7); // печатается сообщение "111"
fk (3.3, 7.0); // печатается сообщение "22"
*/

#include <iostream>
using namespace std;

class A {
public:
  A(){};
  operator int() { return 0; }
  operator double() { return 0; }
};

void fk(int x, int y) { cout << "111" << endl; }

void fk(double x, double y) { cout << "22" << endl; }

int main() {
  A ob;
  short x = 5;
  fk(ob, 7);
  fk(ob, 3.4);
  fk(x, 7);
  fk(2.4f, 7.0);
  fk(4, 7);
  fk(3.3, 7.0);
  return 0;
}