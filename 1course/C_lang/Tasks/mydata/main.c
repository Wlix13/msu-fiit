#include <stdio.h>
#include "mydata.h"

int main() {
    Complex c1 = {1.0, 2.0};
    Complex c2 = {3.0, 4.0};

    Complex sum = complex_add(c1, c2);
    Complex diff = complex_sub(c1, c2);
    Complex prod = complex_mul(c1, c2);

    complex_print(c1);
    printf("Sum: %.2f + %.2fi\n", sum.real, sum.imag);
    printf("Difference: %.2f + %.2fi\n", diff.real, diff.imag);
    printf("Product: %.2f + %.2fi\n", prod.real, prod.imag);


    return 0;
}
