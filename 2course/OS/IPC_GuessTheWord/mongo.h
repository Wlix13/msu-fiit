#ifndef MONGO_H
#define MONGO_H

#include <bson/bson.h>
#include <mongoc/mongoc.h>

/*
 * This function gets a collection from a database.
 * @param uriString: A string representing the MongoDB URI
 * @param databaseName: A string representing the database name
 * @param collectionName: A string representing the collection name
 * @param client: A **mongoc_client_t struct representing the client
 * @param database: A **mongoc_database_t struct representing the database
 * @return A mongoc_collection_t struct representing the collection
 */
mongoc_collection_t *getCollection(const char *uriString,
                                   const char *databaseName,
                                   const char *collectionName,
                                   mongoc_client_t **client,
                                   mongoc_database_t **database);

/*
 * This function closes the connection to the MongoDB server.
 * @param client: A mongoc_client_t struct representing the client
 * @param database: A mongoc_database_t struct representing the database
 * @param collection: A mongoc_collection_t struct representing the collection
 */
void closeConnection(mongoc_client_t *client, mongoc_database_t *database,
                     mongoc_collection_t *collection);

/*
 * This function gets a word from a collection by its _id.
 * @param collection: A mongoc_collection_t struct representing collection
 * @param id: A string representing _id of document to get
 * @return A string representing the word
 */
char *getWordById(mongoc_collection_t *collection, const char *id);

/*
 * This function gets a hint from a collection by its _id.
 * @param collection: A mongoc_collection_t struct representing collection
 * @param id: A string representing _id of document to get
 * @return A string representing the hint
 */
char *getHintById(mongoc_collection_t *collection, const char *id);

/*
 * This function gets a factor from a collection by its _id.
 * @param collection: A mongoc_collection_t struct representing collection
 * @param id: A string representing _id of document to get
 * @return A double representing the factor
 */
double getFactorById(mongoc_collection_t *collection, const char *id);

/*
 * This function gets the document with the smallest factor from a collection.
 * @param collection: A mongoc_collection_t struct representing collection
 * @return A string representing the _id of the document
 */
char *idSmallestFactor(mongoc_collection_t *collection);

/*
 * This function increments the factor of a document by its _id.
 * @param collection: A mongoc_collection_t struct representing collection
 * @param id: A string representing _id of document to increment
 * @param increment: A double representing the increment
 */
void incrementFactorById(mongoc_collection_t *collection, const char *id,
                         const double increment);

#endif
