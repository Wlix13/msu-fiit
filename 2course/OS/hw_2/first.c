/*
Напишите функцию rev_bit с прототипом

STYPE rev_bit(STYPE value);
Функция меняет порядок бит в числе на противоположный. Например, рассмотрим
4-битное целое число 0101. Поменяв порядок бит на противоположный, получим число
1010. Однако, если то же число рассматривать как 8-битное, обратный порядок бит
будет равен 10100000.
Измененное число вернуть как результат.

STYPE — это некоторый целый знаковый тип. UTYPE — это некоторый целый
беззнаковый тип того же размера, что и STYPE. Определите типы STYPE и UTYPE в
своей программе, используя typedef следующим образом:
typedef int STYPE;
typedef unsigned int UTYPE;

В main получите число со стандартного ввода, вызовите для него функцию. Выведите
число на экран в двоичном виде до и после изменения.


*/

#include <stdio.h>

typedef signed int STYPE;
typedef unsigned int UTYPE;

/*
Function to print binary form of number
Get:
    'STYPE value' - number to print
Return:
    'void'
*/
void print_binary(STYPE value) {
  int num_bits = sizeof(STYPE) * 8;

  for (int i = num_bits - 1; i >= 0; i--) {
    printf("%d", (value >> i) & 1);
  }
  printf("\n");
}

/*
Function to reverse bits of num
Get:
    'STYPE value' - number to reverse bits
Return:
    'STYPE' - reversed number
*/
STYPE rev_bit(STYPE value) {

  UTYPE result = 0;
  int num_bits = sizeof(STYPE) * 8;

  for (int i = 0; i < num_bits; i++) {
    UTYPE bit = (value >> i) & 1;
    result |= (bit << (num_bits - 1 - i));
  }

  return (STYPE)result;
}

int main() {
  STYPE num;

  printf("Enter a number: ");
  scanf("%d", &num);

  printf("Source number in binary form: ");
  print_binary(num);

  STYPE reversed_num = rev_bit(num);

  printf("Number after inverting the bit order: ");
  print_binary(reversed_num);
  return 0;
}