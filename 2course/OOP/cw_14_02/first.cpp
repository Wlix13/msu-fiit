/*
Описать класс rational для представления действительного числа в виде
обыкновенной дроби (члены-данные класса - числитель и знаменатель).
Для работы с объектами класса напишите конструктор, позволяющий строить объект
по заданным значениям числителя и знаменателя или по заданному значению
числителя (знаменатель в этом случае считать равным 1).
Если дробь представляет собой отрицательное число, минус ставится в числителе.
Если значения задают сократимую дробь, она должна быть сокращена в этом
конструкторе.
Для полученного класса перегрузите операцию "+".
Операция должна быть применима для двух дробей.
*/

#include <iostream>
using namespace std;

class Rational {
  int numerator;
  int denominator;

public:
  Rational(int num, int den) {
    if (den == 0) {
      cout << "Denominator can't be 0" << endl;
      return;
    }

    int gcd = 1;
    // Find the greatest common divisor
    for (int i = 1; i <= num && i <= den; i++) {
      if (num % i == 0 && den % i == 0) {
        gcd = i;
      }
    }

    numerator = num / gcd;
    denominator = den / gcd;
  }

  Rational(int num) {
    numerator = num;
    denominator = 1;
  }

  // If number is negative, put minus in numerator
  void print() {
    if (denominator < 0) {
      numerator *= -1;
      denominator *= -1;
    }
    cout << numerator << "/" << denominator << endl;
  }

  void plus(Rational &r) {
    int num = numerator * r.denominator + r.numerator * denominator;
    int den = denominator * r.denominator;
    cout << num << "/" << den << endl;
  }

  Rational operator+(Rational &r) {
    int num = numerator * r.denominator + r.numerator * denominator;
    int den = denominator * r.denominator;
    return Rational(num, den);
  }
};

int main() {
  Rational r1(-1, 2);
  Rational r2(-1, 2);
  Rational r3 = r1 + r2;
  Rational r4(1, 3);
  r3.print();
  r4.plus(r3);

  return 0;
}