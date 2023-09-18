/*
Написать функцию, параметр – unsigned int x.

Если в x старший !байт! не равен его младшему байту, поменять эти байты местами,
иначе обнулить остальные (все, кроме старшего и младшего) байты в x.

В main получите число со стандартного ввода, вызовите для него функцию  (можно в
цикле). Выведите число на экран в двоичном виде до и после изменения.
*/

#include <stdio.h>

void print_binary(unsigned int x) {
  for (int i = 31; i >= 0; i--) {
    printf("%u", (x >> i) & 1);
  }
  printf("\n");
}

unsigned int modify_bytes(unsigned int x) {
  // Get high byte
  unsigned int highByte = (x & 0xFF000000) >> 24;
  // Get low byte
  unsigned int lowByte = x & 0x000000FF;

  if (highByte != lowByte) {
    // Swap the high byte and low byte
    x = (x & 0x00FFFF00) | (highByte) | (lowByte << 24);
  } else {
    // Zero all other bytes
    x = (highByte << 24) | lowByte;
  }

  return x;
}

int main() {
  unsigned int num;
  printf("Enter a number: ");
  scanf("%u", &num);

  printf("\nBefore modification: ");
  print_binary(num);

  unsigned int modified_num = modify_bytes(num);

  printf("\nAfter Modification: ");
  print_binary(modified_num);

  return 0;
}