#ifndef MYDATA_H
#define MYDATA_H

typedef struct Complex {
  double real;
  double imag;
} Complex;

Complex complex_add(Complex c1, Complex c2);
Complex complex_sub(Complex c1, Complex c2);
Complex complex_mul(Complex c1, Complex c2);
void complex_print(Complex c1);

#endif
