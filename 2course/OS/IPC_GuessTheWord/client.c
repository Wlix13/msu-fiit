#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

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
  char *message = "Hello from client";
  char buffer[1024] = {0};

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

  // Send a message to the server
  send(sock, message, strlen(message), 0);
  printf("Message sent\n");

  // Receive a response from the server
  read(sock, buffer, 1024);
  printf("Message from server: %s\n", buffer);

  // Close the socket
  close(sock);

  return 0;
}
