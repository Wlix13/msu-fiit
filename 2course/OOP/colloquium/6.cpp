/*
Даны описания структуры, переменной и функции. Дополните описания структуры
mm(не изменяя описание функции f) так, чтобы только описании f стало ошибочным.
struct mm{ int a,b;} ;
int i = sizeof(mm);
int f(mm s){ return 0; }
*/

#include <iostream>

using namespace std;
struct mm {
  int a, b;
  mm(int x, int y) : a(x), b(y) {} // Конструктор с двумя параметрами
};
// Или так
struct mm {
  int a, b;

private:
  mm() {} // Закрытый конструктор без параметров
};