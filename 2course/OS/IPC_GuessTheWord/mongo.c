#include "mongo.h"
#include <stdlib.h>
#include <string.h>

mongoc_collection_t *getCollection(const char *uriString,
                                   const char *databaseName,
                                   const char *collectionName,
                                   mongoc_client_t **client,
                                   mongoc_database_t **database) {
  mongoc_uri_t *uri;
  bson_error_t error;

  // Initialize libmongoc's internals
  mongoc_init();

  // Safely create a MongoDB URI object from the given string
  uri = mongoc_uri_new_with_error(uriString, &error);
  if (!uri) {
    fprintf(stderr,
            "failed to parse URI: %s\n"
            "error message:       %s\n",
            uriString, error.message);
    return NULL;
  }

  // Create a new client instance
  *client = mongoc_client_new_from_uri(uri);
  mongoc_uri_destroy(uri);
  if (!*client) {
    return NULL;
  }

  // Get the specified database and collection
  *database = mongoc_client_get_database(*client, databaseName);
  return mongoc_database_get_collection(*database, collectionName);
}

void closeConnection(mongoc_client_t *client, mongoc_database_t *database,
                     mongoc_collection_t *collection) {
  if (collection) {
    mongoc_collection_destroy(collection);
  }
  if (database) {
    mongoc_database_destroy(database);
  }
  if (client) {
    mongoc_client_destroy(client);
  }
  mongoc_cleanup();
}

void insertUpdateDocument(mongoc_collection_t *collection, const char *id,
                          const char *word, const double factor) {
  bson_t *query, *update, child;
  mongoc_cursor_t *cursor;
  const bson_t *doc;
  bool document_exists = false;
  bson_error_t error;

  // Create a query for the document with a specific _id
  query = bson_new();
  BSON_APPEND_UTF8(query, "_id", id);

  // Find the document
  cursor = mongoc_collection_find_with_opts(collection, query, NULL, NULL);
  if (mongoc_cursor_next(cursor, &doc)) {
    document_exists = true;
  }

  // Update the document if it exists
  if (document_exists) {
    update = bson_new();
    BSON_APPEND_DOCUMENT_BEGIN(update, "$set", &child);
    BSON_APPEND_UTF8(&child, "word", word);
    BSON_APPEND_DOUBLE(&child, "factor", factor);
    bson_append_document_end(update, &child);

    if (!mongoc_collection_update_one(collection, query, update, NULL, NULL,
                                      &error)) {
      fprintf(stderr, "Update failed: %s\n", error.message);
    }

    bson_destroy(update);
  } else {
    // The document does not exist, insert a new one
    BSON_APPEND_UTF8(query, "word", word);
    BSON_APPEND_DOUBLE(query, "factor", factor);

    if (!mongoc_collection_insert_one(collection, query, NULL, NULL, &error)) {
      fprintf(stderr, "Insert failed: %s\n", error.message);
    }
  }

  bson_destroy(query);
  mongoc_cursor_destroy(cursor);
}

void getDocument(mongoc_collection_t *collection, const char *id) {
  bson_t *query;
  mongoc_cursor_t *cursor;
  const bson_t *doc;

  // Create a query for the document with a specific _id
  query = bson_new();
  BSON_APPEND_UTF8(query, "_id", id);

  // Find the document
  cursor = mongoc_collection_find_with_opts(collection, query, NULL, NULL);
  if (mongoc_cursor_next(cursor, &doc)) {
    char *str = bson_as_json(doc, NULL);
    printf("%s\n", str);
    bson_free(str);
  } else {
    fprintf(stderr, "Document not found\n");
  }

  bson_destroy(query);
  mongoc_cursor_destroy(cursor);
}

void deleteDocument(mongoc_collection_t *collection, const char *id) {
  bson_t *query;
  bson_error_t error;

  // Create a query for the document with a specific _id
  query = bson_new();
  BSON_APPEND_UTF8(query, "_id", id);

  // Delete the document
  if (!mongoc_collection_delete_one(collection, query, NULL, NULL, &error)) {
    fprintf(stderr, "Delete failed: %s\n", error.message);
  }

  bson_destroy(query);
}

char *wordSmallestFactor(mongoc_collection_t *collection) {
  char *word = NULL;
  const char *id = NULL;
  double factor = 0.0;
  const bson_t *doc;
  bson_t *query, *opts;
  bson_iter_t iter;
  mongoc_cursor_t *cursor;

  // Create an empty query
  query = bson_new();

  // Create query options with sorting by 'factor' in ascending order
  opts = BCON_NEW("sort", "{", "factor", BCON_DOUBLE(1), "}");

  // Execute the query with options
  cursor = mongoc_collection_find_with_opts(collection, query, opts, NULL);

  // Retrieve the first document
  if (mongoc_cursor_next(cursor, &doc)) {
    bson_iter_init(&iter, doc);
    if (bson_iter_find(&iter, "word") && BSON_ITER_HOLDS_UTF8(&iter)) {
      word = strdup(bson_iter_utf8(&iter, NULL)); // Duplicate the string
      bson_iter_init(&iter, doc);
      bson_iter_find(&iter, "_id");
      id = bson_iter_utf8(&iter, NULL);
      bson_iter_init(&iter, doc);
      bson_iter_find(&iter, "factor");
      factor = bson_iter_double(&iter);
      insertUpdateDocument(collection, id, word, factor + 1.0);
    }
  } else {
    fprintf(stderr, "Document does not contain 'word' field\n");
    return NULL;
  }

  // Clean up
  bson_destroy(query);
  bson_destroy(opts);
  mongoc_cursor_destroy(cursor);

  return word;
}

// int main(int argc, char const *argv[]) {
//   // MongoDB URI connection string
//   const char *uriString = "mongodb://127.0.0.1:27017";

//   mongoc_client_t *client;
//   mongoc_database_t *database;
//   mongoc_collection_t *collection;

//   collection = getCollection(uriString, "IPC", "words", &client, &database);

//   if (!collection) {
//     fprintf(stderr, "Failed to get collection\n");
//     exit(EXIT_FAILURE);
//   }

//   // Call the function to insert document
//   // if (argc > 3) {
//   //   insertUpdateDocument(collection, argv[1], argv[2], strtod(argv[3],
//   //   NULL));
//   // } else {
//   //   fprintf(stderr, "Not enough arguments\n");
//   // }

//   // Call the function to get document
//   // if (argc > 1) {
//   //   getDocument(collection, argv[1]);
//   // } else {
//   //   fprintf(stderr, "Not enough arguments\n");
//   // }

//   // Call the function to delete document
//   // if (argc > 1) {
//   //   deleteDocument(collection, argv[1]);
//   // } else {
//   // fprintf(stderr, "Not enough arguments\n");
//   // }

//   // Get word
//   char *word = wordSmallestFactor(collection);
//   printf("%s\n", word);

//   // Clean up
//   closeConnection(client, database, collection);
//   free((void *)word);

//   return 1;
// }