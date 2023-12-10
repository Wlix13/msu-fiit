#include "mongo.h"
#include <netinet/in.h>
#include <pthread.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>

#define MAX_CLIENTS 10
#define BUFFER_SIZE 1024
#define MESSAGE_LENGTH 1024
#define MONGODB_URI "mongodb://localhost:27017"

// Global variables for MongoDB
mongoc_client_t *client;
mongoc_database_t *database;
mongoc_collection_t *collection;
/*
 * Function to update the word progress.
 * @param word: A string representing word
 * @param guess: A string representing guess
 * @param wordProgress: A string representing word progress
 */
void updateWordProgress(const char *word, const char *guess,
                        char *wordProgress) {
  int length = strlen(word);
  for (int i = 0; i < length; i++) {
    if (word[i] == guess[0]) {
      wordProgress[i] = guess[0];
    }
  }
}

/*
 * This function checks if the word is completed.
 * @param word: A string representing the word
 * @param wordProgress: A string representing the word progress
 */
int isWordCompleted(const char *word, const char *wordProgress) {
  return strcmp(wordProgress, word) == 0;
}

/*
 * Handles communication with the client:
 * 1. Waits for the client to start the game
 * 2. Gets word from MongoDB
 * 3. Accepts guesses
 * 4. Sends responses
 * 5. Updates the factor in MongoDB
 */
void *clientHandler(void *socket) {
  int sock = *(int *)socket;
  int valread;
  char *word, *hint, *id;

  // Get the word with the smallest factor
  id = idSmallestFactor(collection);
  word = getWordById(collection, id);
  hint = getHintById(collection, id);
  printf("Word: %s, ID: %s\n", word, id);

  char clientMsg[MESSAGE_LENGTH];
  char response[BUFFER_SIZE];
  char wordProgress[strlen(word) + 1];
  bool gameStarted = false;
  bool gameWon = false;

  memset(wordProgress, '_', strlen(word));
  wordProgress[strlen(word)] = '\0';

  // Communication with client
  while ((valread = read(sock, clientMsg, MESSAGE_LENGTH - 1)) > 0) {
    clientMsg[valread] = '\0';

    if (!gameStarted && strcmp(clientMsg, "start") == 0) {
      sprintf(response, "Game started. \nWord length: %lu. Hint: %s",
              strlen(word), hint);
      gameStarted = true;
    } else if (gameStarted) {
      if (strlen(clientMsg) == 1) {
        // Single letter guess
        updateWordProgress(word, clientMsg, wordProgress);
        if (isWordCompleted(word, wordProgress)) {
          sprintf(response, "Congratulations! Correct word guessed.");
          send(sock, response, strlen(response), 0);
          gameWon = true;
          break;
        } else {
          sprintf(response, "Current Progress: %s", wordProgress);
        }
      } else if (strcmp(clientMsg, word) == 0) {
        sprintf(response, "Congratulations! Correct word guessed.");
        send(sock, response, strlen(response), 0);
        gameWon = true;
        break;
      } else {
        sprintf(response, "Incorrect guess. Game over.");
        send(sock, response, strlen(response), 0);
        break;
      }
    } else {
      strcpy(response, "Please start the game first by sending 'start'.");
    }

    send(sock, response, strlen(response), 0);
  }

  if (valread == 0) {
    printf("Client disconnected\n");
  } else if (valread == -1) {
    perror("Recv failed");
  }

  // Update the factor based on the game outcome
  if (gameWon) {
    incrementFactorById(collection, id, 3.0);
  } else {
    incrementFactorById(collection, id, 1.0);
  }

  free(word);
  free(hint);
  free(id);
  close(sock);
  free(socket);
  return 0;
}

int main(int argc, char *argv[]) {
  if (argc != 2) {
    fprintf(stderr, "Usage: %s <port>\n", argv[0]);
    exit(EXIT_FAILURE);
  }

  // Port validation(<1024 are reserved)
  int PORT = strtol(argv[1], NULL, 10);
  if (PORT < 1024 || PORT > 65535) {
    fprintf(stderr, "Port number should be between 1024 and 65535\n");
    exit(EXIT_FAILURE);
  }

  // Connect to MongoDB
  collection = getCollection(MONGODB_URI, "IPC", "words", &client, &database);
  if (!collection) {
    fprintf(stderr, "Failed to connect to MongoDB collection\n");
    exit(EXIT_FAILURE);
  }

  int sock, new_socket, *new_sock;
  struct sockaddr_in address;
  int addrlen = sizeof(address);
  pthread_t thread_id;

  // Create socket
  if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
    perror("Socket failed");
    exit(EXIT_FAILURE);
  }

  // Setting address and port
  address.sin_family = AF_INET;
  address.sin_addr.s_addr = INADDR_ANY;
  address.sin_port = htons(PORT);

  // Binding the socket
  if (bind(sock, (struct sockaddr *)&address, sizeof(address)) < 0) {
    perror("Bind failed");
    exit(EXIT_FAILURE);
  }
  if (listen(sock, MAX_CLIENTS) < 0) {
    perror("Listen");
    exit(EXIT_FAILURE);
  }

  // Accepting incoming connections
  while ((new_socket = accept(sock, (struct sockaddr *)&address,
                              (socklen_t *)&addrlen))) {
    new_sock = malloc(sizeof(int));
    *new_sock = new_socket;

    if (pthread_create(&thread_id, NULL, clientHandler, (void *)new_sock) < 0) {
      perror("Could not create thread");
      exit(EXIT_FAILURE);
    }

    // Detach the thread so that it doesn't have to be joined
    pthread_detach(thread_id);

    printf("Client connected\n");
  }

  if (new_socket < 0) {
    perror("Accept failed");
    exit(EXIT_FAILURE);
  }

  // Close the socket
  close(sock);

  // Close the connection to MongoDB
  closeConnection(client, database, collection);
  return 0;
}
