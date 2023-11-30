/*
Севрер получает от клиента или букву или слово. Если буква, то проверяет есть ли
она в слове и отсылает клиенту в каких позициях она находится. Если буквы нет,
то отсылает клиенту сообщение о том, что буквы нет. Если клиент угадал все
буквы, то отсылает клиенту сообщение о том, что он выиграл. Если клиент
отправляет слово, то проверяет совпадает ли оно с загаданным и отсылает клиенту
ответ. Если слово не совпадает, то клиенту отсылается сообщение о том, что он
проиграл.
*/

#include "mongo.h"
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

const char *uriString = "mongodb://127.0.0.1:27017";

void handleClient(int socket) {
  // Start game
  // Wait for client to start the game
  char *word;
  char buffer[1024] = {0};
  send(socket, "Send 'start' to begin", strlen("Send 'start' to begin"), 0);
  int valread = read(socket, buffer, 1024);
  if (valread == 0) {
    return;
  }

  if (strcmp(buffer, "start") == 0) {
    send(socket, "Game started", strlen("Game started"), 0);
    // Init database
    mongoc_client_t *client = NULL;
    mongoc_database_t *database = NULL;
    mongoc_collection_t *collection;
    collection = getCollection(uriString, "IPC", "words", &client, &database);

    if (!collection) {
      fprintf(stderr, "Failed to get collection\n");
      exit(EXIT_FAILURE);
    }

    // Get word from database
    word = wordSmallestFactor(collection);
    printf("%s\n", word);

    // Send word length to client
    char wordLength[10];
    sprintf(wordLength, "%ld", strlen(word));
    send(socket, wordLength, strlen(wordLength), 0);
  } else {
    send(socket, "Game not started", strlen("Game not started"), 0);
    return;
  }
  char *guessedWord = malloc(strlen(word) + 1);
  int guessedLetters = 0;

  while (1) {
    int valread = read(socket, buffer, 1024);
    if (valread == 0) {
      break;
    }

    if (strlen(buffer) == 1) {
      char letter = buffer[0];
      int letterFound = 0;
      for (int i = 0; i < strlen(word); i++) {
        if (word[i] == letter) {
          letterFound = 1;
          guessedWord[i] = letter;
          guessedLetters++;
        }
      }
      if (letterFound) {
        if (guessedLetters == strlen(word)) {
          send(socket, "You won!", strlen("You won!"), 0);
          break;
        }
        send(socket, guessedWord, strlen(guessedWord), 0);
      } else {
        send(socket, "Letter not found", strlen("Letter not found"), 0);
      }
    } else {
      if (strcmp(buffer, word) == 0) {
        send(socket, "You won!", strlen("You won!"), 0);
      } else {
        send(socket, "You lost!", strlen("You lost!"), 0);
      }
      break;
    }
  }
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <port>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  int PORT = strtol(argv[1], NULL, 10);

  if (PORT < 0 || PORT > 65535) {
    fprintf(stderr, "Invalid port number\n");
    exit(EXIT_FAILURE);
  }

  int server_fd, new_socket;
  struct sockaddr_in address;
  int addrlen = sizeof(address);

  // Creating socket file descriptor
  if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
    perror("socket failed");
    exit(EXIT_FAILURE);
  }

  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(PORT);

  // Bind the socket to the address and port number
  if (bind(server_fd, (struct sockaddr *)&address, sizeof(address)) < 0) {
    perror("bind failed");
    exit(EXIT_FAILURE);
  }

  // Listen for incoming connections
  if (listen(server_fd, 3) < 0) {
    perror("listen");
    exit(EXIT_FAILURE);
  }

  // Accept an incoming connection
  if ((new_socket = accept(server_fd, (struct sockaddr *)&address,
                           (socklen_t *)&addrlen)) < 0) {
    perror("accept");
    exit(EXIT_FAILURE);
  }

  // Handle the client
  handleClient(new_socket);

  // Close the socket
  close(server_fd);

  return 0;
}
