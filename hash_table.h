#pragma once
  
#ifndef __HASH_TABLE_H__
#define __HASH_TABLE_H__

typedef struct entry entry_t;
typedef struct hash_table ioopm_hash_table_t;
#include <stdbool.h>
struct entry
{
  int key;       // holds the key
  char *value;   // holds the value
  entry_t *next; // points to the next entry (possibly NULL)
};

struct hash_table
{
  entry_t buckets[17];
};

typedef bool(*ioopm_apply_function)(int key, char *value, void *extra);

/// @brief Create a new hash table
/// @return A new empty hash table
ioopm_hash_table_t *ioopm_hash_table_create();

/// @brief add key => value entry in hash table ht
/// @param ht hash table operated upon
/// @param key key to insert
/// @param value value to insert
void ioopm_hash_table_insert(ioopm_hash_table_t *ht, int key, char *value);

/// @brief lookup value for key in hash table ht
/// @param ht hash table operated upon
/// @param key key to lookup
/// @return the value mapped to by key (FIXME: incomplete)
bool ioopm_hash_table_lookup(ioopm_hash_table_t *ht, int key, char **result);

/// @brief remove any mapping from key to a value
/// @param ht hash table operated upon
/// @param key key to remove
/// @return the value mapped to by key (FIXME: incomplete)
bool ioopm_hash_table_remove(ioopm_hash_table_t *ht, int key, char **result);

void ioopm_hash_table_destroy(ioopm_hash_table_t *ht);




/// @brief returns the number of key => value entries in the hash table
/// @param h hash table operated upon
/// @return the number of key => value entries in the hash table
//size_t ioopm_hash_table_size(ioopm_hash_table_t *h);

/// @brief checks if the hash table is empty
/// @param h hash table operated upon
/// @return true is size == 0, else false
bool ioopm_hash_table_is_empty(ioopm_hash_table_t *h);

/// @brief clear all the entries in a hash table
/// @param h hash table operated upon
void ioopm_hash_table_clear(ioopm_hash_table_t *h);

/// @brief return the keys for all entries in a hash map (in no particular order, but same as ioopm_hash_table_values)
/// @param h hash table operated upon
/// @return an array of keys for hash table h
int *ioopm_hash_table_keys(ioopm_hash_table_t *h);

/// @brief return the values for all entries in a hash map (in no particular order, but same as ioopm_hash_table_keys)
/// @param h hash table operated upon
/// @return an array of values for hash table h
char **ioopm_hash_table_values(ioopm_hash_table_t *h);

/// @brief check if a hash table has an entry with a given key
/// @param h hash table operated upon
/// @param key the key sought 
bool ioopm_hash_table_has_key(ioopm_hash_table_t *h, int key);

/// @brief check if a hash table has an entry with a given value
/// @param h hash table operated upon
/// @param value the value sought 
bool ioopm_hash_table_has_value(ioopm_hash_table_t *h, char *value);

/// @brief check if a predicate is satisfied by all entries in a hash table
/// @param h hash table operated upon
/// @param pred the predicate 
/// @param arg extra argument to pred
//bool ioopm_hash_table_all(ioopm_hash_table_t *h, ioopm_apply_function pred, void *arg);

/// @brief check if a predicate is satisfied by any entry in a hash table
/// @param h hash table operated upon
/// @param pred the predicate 
/// @param arg extra argument to pred
//bool ioopm_hash_table_any(ioopm_hash_table_t *h, ioopm_apply_function pred, void *arg);

/// @brief apply a function to all entries in a hash table
/// @param h hash table operated upon
/// @param apply_fun the function to be applied to all elements
/// @param arg extra argument to apply_fun
//void ioopm_hash_table_apply_to_all(ioopm_hash_table_t *h, ioopm_apply_function apply_fun, void *arg);

#endif
