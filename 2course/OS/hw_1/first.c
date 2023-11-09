/*
Написать функцию чтения строки со стандартного ввода.

Длина строки неизвестна, считаем, что любой приготовленный буфер может оказаться
мал. Чтение происходит до ввода ' \n' или EOF. EOF можно ввести нажатием Ctrl-D
(иногда нужно нажать дважды). Если не получается, можно записать строку в файл,
так чтобы на конце не было ' \n', и перенаправить ввод из этого файла так :
./a.out <file

Функция должна вернуть указатель на введенную строку.
Реализовать вариант с перераспределением памяти. Дополнительную память выделять
блоками, длина которых кратна 4 (4, 8, 16,...), задать эту длину с помощью
#define. Для тестирования лучше взять небольшой блок, например, 4 байта.

Отслеживать возможное исчерпание памяти (malloc вернет NULL).
Запрещено использовать функцию realloc ( или malloc) для добавления памяти по
одному байту, т.к. это крайне неэффективно. Написать функцию main(), в которой
продемонстрировать работу функции ввода.
*/

#include <stdio.h>
#include <stdlib.h>

#define BLOCK_SIZE 4

char *inputString() {
  char *str = NULL;
  int size = 0;
  int capacity = 0;
  int blockCount = 0;

  while (1) {
    if (size >= capacity) {
      capacity += BLOCK_SIZE;
      blockCount++;

      char *temp = realloc(str, capacity);

      if (temp == NULL) {
        fprintf(stderr, "Memory allocation failed. Exiting.\n");
        free(str);
        return NULL;
      }

      str = temp;
    }

    int ch = getchar();

    if (ch == EOF || ch == '\n') {
      str[size] = '\0';
      break;
    }

    str[size++] = (char)ch;
  }

  if (blockCount > 1) {
    printf("Memory reallocated %d times with size of blocks - %d bytes.\n",
           blockCount - 1, BLOCK_SIZE);
  }

  return str;
}

int main() {
  printf("Enter a string: \n");
  char *input = inputString();

  if (input != NULL) {
    printf("You entered: %s\n", input);
    free(input);
  }

  return 0;
}