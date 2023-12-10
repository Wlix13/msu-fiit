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

char *getWordById(mongoc_collection_t *collection, const char *id) {
  bson_t *query;
  mongoc_cursor_t *cursor;
  const bson_t *doc;
  char *word = NULL;
  bson_iter_t iter;

  // Create a query for the document with a specific _id
  query = bson_new();
  BSON_APPEND_UTF8(query, "_id", id);

  // Find the document
  cursor = mongoc_collection_find_with_opts(collection, query, NULL, NULL);
  if (mongoc_cursor_next(cursor, &doc)) {
    bson_iter_init(&iter, doc);
    if (bson_iter_find(&iter, "word") && BSON_ITER_HOLDS_UTF8(&iter)) {
      word = strdup(bson_iter_utf8(&iter, NULL)); // Duplicate the string
    }
  } else {
    fprintf(stderr, "Document not found\n");
  }

  // Clean up
  bson_destroy(query);
  mongoc_cursor_destroy(cursor);

  return word;
}

char *getHintById(mongoc_collection_t *collection, const char *id) {
  bson_t *query;
  mongoc_cursor_t *cursor;
  const bson_t *doc;
  char *hint = NULL;
  bson_iter_t iter;

  // Create a query for the document with a specific _id
  query = bson_new();
  BSON_APPEND_UTF8(query, "_id", id);

  // Find the document
  cursor = mongoc_collection_find_with_opts(collection, query, NULL, NULL);
  if (mongoc_cursor_next(cursor, &doc)) {
    bson_iter_init(&iter, doc);
    if (bson_iter_find(&iter, "hint") && BSON_ITER_HOLDS_UTF8(&iter)) {
      hint = strdup(bson_iter_utf8(&iter, NULL)); // Duplicate the string
    }
  } else {
    fprintf(stderr, "Document not found\n");
  }

  // Clean up
  bson_destroy(query);
  mongoc_cursor_destroy(cursor);

  return hint;
}

double getFactorById(mongoc_collection_t *collection, const char *id) {
  bson_t *query;
  mongoc_cursor_t *cursor;
  const bson_t *doc;
  double factor = 0;
  bson_iter_t iter;

  // Create a query for the document with a specific _id
  query = bson_new();
  BSON_APPEND_UTF8(query, "_id", id);

  // Find the document
  cursor = mongoc_collection_find_with_opts(collection, query, NULL, NULL);
  if (mongoc_cursor_next(cursor, &doc)) {
    bson_iter_init(&iter, doc);
    if (bson_iter_find(&iter, "factor") && BSON_ITER_HOLDS_UTF8(&iter)) {
      factor = bson_iter_double(&iter);
    }
  } else {
    fprintf(stderr, "Document not found\n");
  }

  // Clean up
  bson_destroy(query);
  mongoc_cursor_destroy(cursor);

  return factor;
}

char *idSmallestFactor(mongoc_collection_t *collection) {
  char *id = NULL;
  const bson_t *doc;
  bson_t *query, *opts;
  bson_iter_t iter;
  mongoc_cursor_t *cursor;

  // Create an empty query
  query = bson_new();

  // Create query options with sorting by 'factor' in ascending order
  opts = BCON_NEW("sort", "{", "factor", BCON_INT32(1), "}");

  // Execute the query with options
  cursor = mongoc_collection_find_with_opts(collection, query, opts, NULL);

  // Retrieve the first document
  if (mongoc_cursor_next(cursor, &doc)) {
    bson_iter_init(&iter, doc);
    if (bson_iter_find(&iter, "_id") && BSON_ITER_HOLDS_UTF8(&iter)) {
      id = strdup(bson_iter_utf8(&iter, NULL)); // Duplicate the string
    }
  } else {
    fprintf(stderr, "No document found\n");
  }

  // Clean up
  bson_destroy(query);
  bson_destroy(opts);
  mongoc_cursor_destroy(cursor);

  return id;
}

void incrementFactorById(mongoc_collection_t *collection, const char *id,
                         const double increment) {
  bson_t *query, *update, child;
  bson_error_t error;

  // Create a query for the document with a specific _id
  query = bson_new();
  BSON_APPEND_UTF8(query, "_id", id);

  // Prepare the update to increment the factor
  update = bson_new();
  BSON_APPEND_DOCUMENT_BEGIN(update, "$inc", &child);
  BSON_APPEND_DOUBLE(&child, "factor", increment);
  bson_append_document_end(update, &child);

  // Perform the update
  if (!mongoc_collection_update_one(collection, query, update, NULL, NULL,
                                    &error)) {
    fprintf(stderr, "Increment failed: %s\n", error.message);
  }

  // Clean up
  bson_destroy(query);
  bson_destroy(update);
}
