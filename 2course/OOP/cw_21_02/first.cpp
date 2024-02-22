/*
Для класса rational (АТД) перегрузите операции:
1) "-" с помощью функций - члена класса.
Операция должна быть применима для двух дробей и для первого аргумента - дроби и
второго - целого числа. Если в результате операций получается сократимая дробь,
ее нужно сократить.
2) "*" с помощью внешних функций. Операция должна быть применима для двух
дробей, для первого аргумента - дроби и второго - целого числа и, наоборот, для
числа и дроби. Если в результате операций получается сократимая дробь, ее нужно
сократить.
3) унарный минус - значение дроби меняется на противоположное по модулю - с
помощью внешних функций.
4) присваивание - так, чтобы выражение 7 + (дробь1=дробь2) выполнялось без
перегрузки операции +
5) сравнения на равенство двух дробей (чл.кл. или другом)
6) "++a" префиксную, чл.класса, содержимое - на ваше усмотрение
7) приведение типов (дроби к float)
8) "a++" постфиксную, с помощью внешних функций, содержимое - на ваше усмотрение
9) вывода дроби на печать в виде а / b
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

  Rational operator-(Rational &r) {
    int num = numerator * r.denominator - r.numerator * denominator;
    int den = denominator * r.denominator;
    return Rational(num, den);
  }

  Rational operator-(int num) {
    int num1 = num * denominator - numerator;
    return Rational(num1, denominator);
  }

  friend Rational operator*(Rational &r1, int num);

  friend Rational operator*(int num, Rational &r1);

  friend Rational operator-(Rational &r1);

  Rational operator=(Rational &r) {
    numerator = r.numerator;
    denominator = r.denominator;
    return *this;
  }

  bool operator==(Rational &r) {
    return (numerator == r.numerator && denominator == r.denominator);
  }

  Rational operator++() {
    numerator += denominator;
    return *this;
  }

  operator float() { return (float)numerator / denominator; }

  friend Rational operator++(Rational &r, int);

  friend ostream &operator<<(ostream &os, Rational &r);
};

Rational operator*(Rational &r1, int num) {
  int num1 = r1.numerator * num;
  return Rational(num1, r1.denominator);
}

Rational operator*(int num, Rational &r1) {
  int num1 = r1.numerator * num;
  return Rational(num1, r1.denominator);
}

Rational operator-(Rational &r1) {
  int num = r1.numerator * -1;
  return Rational(num, r1.denominator);
}

Rational operator++(Rational &r, int) {
  Rational temp = r;
  r.numerator += r.denominator;
  return temp;
}

ostream &operator<<(ostream &os, Rational &r) {
  os << r.numerator << "/" << r.denominator;
  return os;
}

int main() {

  Rational r1(3, 5);
  Rational r2(2, 10);
  // Rational r3 = r1 + r2;
  // Rational r4(1, 3);
  // r3.print();
  // r4.plus(r3);

  Rational r5 = r1 - r2;
  cout << "-: " << r5 << endl;

  Rational r6 = r1 * 2;
  cout << "*: " << r6 << endl;

  Rational r7 = 2 * r1;
  cout << "*: " << r7 << endl;

  Rational r8 = -r1;
  cout << "-: " << r8 << endl;

  Rational r9 = 7 + (r1 = r2);
  cout << "=: " << r9 << endl;

  cout << "==: " << (r1 == r2) << endl;

  Rational r10 = ++r1;
  cout << "++: " << r10 << endl;

  cout << "float: " << (float)r1 << endl;

  Rational r11 = r1++;
  cout << "++: " << r11 << ", " << r1 << endl;

  return 0;
}