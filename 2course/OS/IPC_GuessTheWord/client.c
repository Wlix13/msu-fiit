/*
Клиент отправляет серверу или букву, или слово. Сервер отвечает, в каких
позициях в слове находится эта буква или слово. Если клиент угадал слово,
сервер отвечает об этом и закрывает соединение.
*/

#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

void work(int socket) {
  char buffer[1024] = {0};

  // Server sends a hello message
  int valread = read(socket, buffer, 1024);
  if (valread == 0) {
    return;
  }
  printf("%s\n", buffer);

  // Send a start message
  scanf("%s", buffer);
  send(socket, buffer, strlen(buffer), 0);

  // Print response and word length
  valread = read(socket, buffer, 1024);
  if (valread == 0) {
    return;
  }
  printf("%s\n", buffer);
  valread = read(socket, buffer, 1024);
  if (valread == 0) {
    return;
  }
  printf("%s\n", buffer);

  while (1) {
    // Send letter or word
    scanf("%s", buffer);
    send(socket, buffer, strlen(buffer), 0);

    // Get response
    valread = read(socket, buffer, 1024);
    if (valread == 0) {
      return;
    }
    printf("%s\n", buffer);

    if (strcmp(buffer, "You won!") == 0) {
      return;
    }
    if (strcmp(buffer, "You lost!") == 0) {
      return;
    }
  }
}

int main(int argc, char *argv[]) {
  if (argc != 3) {
    fprintf(stderr, "Usage: %s <ip> <port>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  char *IP = argv[1];
  int PORT = strtol(argv[2], NULL, 10);
  if (PORT < 0 || PORT > 65535) {
    fprintf(stderr, "Invalid port number\n");
    exit(EXIT_FAILURE);
  }

  int sock = 0;
  struct sockaddr_in serv_addr;

  // Create a socket
  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    printf("\n Socket creation error \n");
    exit(EXIT_FAILURE);
  }

  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(PORT);

  // Convert IPv4 and IPv6 addresses from text to binary formc
  if (inet_pton(AF_INET, IP, &serv_addr.sin_addr) <= 0) {
    printf("\nInvalid address / Address not supported \n");
    exit(EXIT_FAILURE);
  }

  // Connect to the server
  if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
    printf("\nConnection Failed \n");
    exit(EXIT_FAILURE);
  }

  work(sock);

  // Close the socket
  close(sock);

  return 0;
}
