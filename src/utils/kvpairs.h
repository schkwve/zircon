#ifndef _UTILS_KVPAIRS_H
#define _UTILS_KVPAIRS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <config.h>

#define MAX_KEY_LEN 512
#define MAX_VALUE_LEN 512
#define MAX_PAIRS 100

/* Struct to hold a key-value pair */
typedef struct {
    char key[MAX_KEY_LEN];
    char value[MAX_VALUE_LEN];
} KeyValuePair;

/* Struct to hold an array of key-value pairs */
typedef struct {
    KeyValuePair pairs[MAX_PAIRS];
    int count;
} KeyValueArray;

/* Function to read key-value pairs from a file */
int read_key_value_file(const char *filename, KeyValueArray *kvArray, const struct zircon_config *config);

/* Function to print all key-value pairs */
void print_key_value_pairs(const KeyValueArray *kvArray);

/* Function to get the value associated with a key */
char* get_value(KeyValueArray *kvArray,const char *key);

#endif /* _UTILS_KVPAIRS_H */
