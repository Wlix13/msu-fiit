#ifndef MONGO_H
#define MONGO_H

#include <mongoc/mongoc.h>
#include <bson/bson.h>

/*
 * This function gets a collection from a database.
 * The function takes the following parameters:
 * - uriString: A URI string of the MongoDB server
 * - databaseName: A string name of database
 * - collectionName: A string name of collection
 * - client: A **mongoc_client_t struct representing the client
 * - database: A **mongoc_database_t struct representing the database
 */
mongoc_collection_t *getCollection(const char *uriString,
                                   const char *databaseName,
                                   const char *collectionName,
                                   mongoc_client_t **client,
                                   mongoc_database_t **database);

/*
 * This function closes the connection to the MongoDB server.
 * The function takes the following parameters:
 * - client: A *mongoc_client_t struct representing the client
 * - database: A **mongoc_database_t struct representing the database
 * - collection: A **mongoc_collection_t struct representing the collection
 */
void closeConnection(mongoc_client_t *client, mongoc_database_t *database,
                     mongoc_collection_t *collection);

/*
 * This function inserts or updates a document in a collection.
 * The function takes the following parameters:
 * - collection: A mongoc_collection_t struct representing collection
 * - id: A string representing _id of document
 * - word: A string representing word field of document
 * - factor: A double representing factor field of document
 */
void insertUpdateDocument(mongoc_collection_t *collection, const char *id,
                          const char *word, const double factor);

/*
 * This function gets a document from a collection.
 * The function takes the following parameters:
 * - collection: A mongoc_collection_t struct representing collection
 * - id: A string representing _id of document to get
 */
void getDocument(mongoc_collection_t *collection, const char *id);

/*
 * This function deletes a document from a collection.
 * The function takes the following parameters:
 * - collection: A mongoc_collection_t struct representing collection
 * - id: A string representing _id of document to delete
 */
void deleteDocument(mongoc_collection_t *collection, const char *id);

/*
 * This function gets the document with the smallest factor from a collection
 * and increments its factor by 1.
 * The function takes the following parameters:
 * - collection: A mongoc_collection_t struct representing collection
 */
char *wordSmallestFactor(mongoc_collection_t *collection);

#endif
