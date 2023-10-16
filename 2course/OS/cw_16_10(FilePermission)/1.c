/*
1) Напишите функцию, параметр const char *str - права доступа к файлу в формате
rwx (9 знаков). Указатель str может принимать значение NULL.
Функция должна вернуть соответствующее целое значение прав доступа, либо -1,
если строка не является корректной записью прав доступа. Корректная запись
состоит только из символов '-, 'T', 'w', 'х', расположенных в правильном
порядке.
Указание: используйте строку-образец "rwxrwxrwx" для разбора входной строки. В
функции не должны использоваться константы 3, 8, 9, 10 (даже в виде enum или
#define). Используйте битовые операции.
Поскольку строка-образец является константной, ее длину можно вычислить за
константное время на этапе компиляции. В функции может использоваться не более
одного вызова strlen.
Результат работы функции вывести на экран в виде 8-ричного числа.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int strToMode(const char *str) {
  if (!str)
    return -1;

  const char pattern[] = "rwxrwxrwx";
  const int pattern_length = sizeof(pattern) - 1;

  if (strlen(str) != pattern_length)
    return -1;

  int result = 0;
  for (int i = 0; i < pattern_length; i++) {
    // Check if character is valid
    if (str[i] != pattern[i] && str[i] != '-')
      return -1;

    // Set bit
    if (str[i] == pattern[i] && str[i] != '-') {
      result |= (1 << (pattern_length - i - 1));
    }
  }
  return result;
}

int main() {
  char test_str[9];
  printf("Enter permissions string: ");
  scanf("%s", test_str);

  int str_result = strToMode(test_str);
  if (str_result != -1) {
    printf("Permissions: %o\n", str_result);
  } else {
    printf("Invalid permissions string.\n");
  }

  return 0;
}