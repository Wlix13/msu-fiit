/*
Дано несколько функций в одной области видимости:
void F(double d, char c);
void F(double d, int c);
void F(int d, const char* c);
и вызов из main функции F(x, ...), где x - типа char.
Укажите в вызове функции F типа пропущенного на месте многоточия аргумента так,
чтобы компилятор зафиксировал ошибку "вызов неоднозначен"
*/

#include <iostream>

using namespace std;
void F(double d, char c);
void F(double d, int c);
void F(int d, const char *c);

int main() {
  char x = 'a';
  float y = 1.0;
  F(x, y);
  return 0;
}