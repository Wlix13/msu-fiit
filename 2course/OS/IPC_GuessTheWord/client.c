#include <arpa/inet.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define MAX_PORT 65535
#define MIN_PORT 1024
#define BUFFER_SIZE 1024
#define MESSAGE_LENGTH 1024

/*
 * Handles communication with the server:
 * 1. Starts the game
 * 2. Accepts guesses
 * 3. Sends responses
 */
void serverHandler(int sock) {
  char buffer[BUFFER_SIZE] = {0};
  char guess[MESSAGE_LENGTH] = {0};
  int valread;

  // Start the game
  send(sock, "start", strlen("start"), 0);

  while (1) {
    // Receive and print the response from the server
    memset(buffer, 0, BUFFER_SIZE);
    valread = read(sock, buffer, BUFFER_SIZE);
    if (valread == 0) {
      break;
    }
    printf("Server: %s\n", buffer);

    // Check if the game is ended
    if (strstr(buffer, "Congratulations") || strstr(buffer, "Game over") ||
        strstr(buffer, "Ptart")) {
      break;
    }

    printf("Enter a letter or guess the word: ");
    scanf("%s", guess);

    // Send the guess to the server
    send(sock, guess, strlen(guess), 0);
  }
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <ip:port>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  char *token;
  char *IP;
  int PORT;

  // Split the input string into IP and port
  token = strtok(argv[1], ":");
  if (token != NULL) {
    IP = token;
    token = strtok(NULL, ":");
    if (token != NULL) {
      PORT = strtol(token, NULL, 10);
    } else {
      fprintf(stderr, "Invalid input. Provide a port number.\n");
      exit(EXIT_FAILURE);
    }
  } else {
    fprintf(stderr,
            "Invalid input. Provide an IP address and a port number.\n");
    exit(EXIT_FAILURE);
  }

  // Port validation(<1024 are reserved)
  if (PORT < MIN_PORT || PORT > MAX_PORT) {
    fprintf(stderr, "Port number should be between 1024 and 65535\n");
    exit(EXIT_FAILURE);
  }

  struct sockaddr_in server_addr;
  int sock = 0;

  // Create socket
  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
    perror("Socket failed");
    exit(EXIT_FAILURE);
  }

  server_addr.sin_family = AF_INET;
  server_addr.sin_port = htons(PORT);

  // Convert IPv4 and IPv6 addresses from text to binary form
  if (inet_pton(AF_INET, IP, &server_addr.sin_addr) <= 0) {
    perror("Invalid address");
    exit(EXIT_FAILURE);
  }

  // Connect to the server
  if (connect(sock, (struct sockaddr *)&server_addr, sizeof(server_addr)) < 0) {
    perror("Connection failed");
    exit(EXIT_FAILURE);
  }

  printf("\nConnected to the server.\n");

  // Handle the game
  serverHandler(sock);

  // Close the socket
  close(sock);
  return 0;
}
