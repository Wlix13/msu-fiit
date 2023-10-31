/*
Двустороннее взаимодействие с использованием каналов.
Необходимо использовать 2 канала.
1. В командной строке передается имя файла.
Процесс-отец создает «сына» (сын один на все время работы).
Отец считывает со стандартного ввода символ с и строку (длина строки ограничена
— задайте константу), записывает строку в файл, затем передает сыну символ и
строку.
Сын подсчитывает, сколько раз данный символ входит в строку, результат выводит в
тот же файл после строки записанной отцом. Отец переходит к чтению следующих
символа и строки и т.д.
Работа продолжается до получения отцом строки «exit».
Синхронизировать работу с файлом с помощью аппарата каналов.
Если работа с файлом осуществляется с использованием функций высокого уровня,
после каждого вывода рекомендуется сбрасывать буфер с помощью вызова функции
fflush.
Завершение процессов также должно быть аккуратным - с закрытием файла
*/

#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#define MAX_STR_LEN 256

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <filename>\n", argv[0]);
    exit(1);
  }

  char *filename = argv[1];
  FILE *file = fopen(filename, "w");
  if (!file) {
    perror("Error opening file");
    exit(1);
  }

  int parent_to_child[2], child_to_parent[2];
  if (pipe(parent_to_child) == -1 || pipe(child_to_parent) == -1) {
    perror("pipe");
    exit(1);
  }

  pid_t pid = fork();

  if (pid < 0) {
    perror("fork");
    exit(1);
  }

  if (pid == 0) {              // Child
    close(parent_to_child[1]); // Close unused write end
    close(child_to_parent[0]); // Close unused read end

    char ch;
    char str[MAX_STR_LEN];
    char ack[] = "ACK"; // Acknowledgment message

    while (1) {
      read(parent_to_child[0], &ch, sizeof(ch));
      read(parent_to_child[0], str, MAX_STR_LEN);

      if (strcmp(str, "exit") == 0) {
        write(child_to_parent[1], ack, sizeof(ack));
        break;
      }

      int count = 0;
      for (int i = 0; str[i] != '\0'; i++) {
        if (str[i] == ch)
          count++;
      }

      fprintf(file, "Count of '%c': %d\n", ch, count);
      fflush(file);

      // Work is done, send acknowledgment message
      write(child_to_parent[1], ack, sizeof(ack));
    }

    close(parent_to_child[0]);
    close(child_to_parent[1]);
    exit(0);
  } else {                     // Parent
    close(parent_to_child[0]); // Close unused read end
    close(child_to_parent[1]); // Close unused write end

    char ch;
    char str[MAX_STR_LEN];
    char ackBuf[4];

    while (1) {
      printf("Enter character and string (\"exit\" to quit): ");
      scanf(" %c", &ch);
      getchar(); // Skip space character
      fgets(str, MAX_STR_LEN, stdin);
      str[strcspn(str, "\n")] = 0; // Remove newline character

      fprintf(file, "Input string: %s\n", str);
      fflush(file);

      write(parent_to_child[1], &ch, sizeof(ch));
      write(parent_to_child[1], str, MAX_STR_LEN);

      // Wait for acknowledgment message
      read(child_to_parent[0], ackBuf, sizeof(ackBuf));

      if (strcmp(str, "exit") == 0)
        break;
    }

    close(parent_to_child[1]);
    close(child_to_parent[0]);
    wait(NULL);
    fclose(file);
  }

  return 0;
}
