// Пусть во входном потоке находится последовательность литеров, заканчивающихся
// точкой(кодировка ASCII). 
// Вариант: c
// c: Выяснить есть ли в данной последовательности хотя бы одна пара символов-соседей 'n' и 'o', т.е 
// образующая сочетания 'n' 'o' или 'o''n'


#include <stdio.h>
int main() {
  char c, prev;
  while ((prev = getchar()) != '.' && prev != EOF) {
    c = getchar();
    if (prev == 'n' && c == 'o') {
      printf("Yes\n");
      return 0;
    } else if (prev == 'o' && c == 'n') {
      printf("Yes\n");
      return 0;
    } else {
      prev = c;
    }
  }
  printf("No\n");
  return 0;
}