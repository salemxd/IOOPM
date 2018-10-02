#include <stdio.h>
#include <stdlib.h>
#include "hash_table.h"
#include <stdbool.h>

#define No_Buckets 17

static entry_t *entry_create(int key, char *value, entry_t *next)
{
  entry_t *new_entry = calloc(1, sizeof(entry_t));
  new_entry->key = key;
  new_entry->value = value;
  new_entry->next = next;
  return new_entry;
}

void entry_destroy(entry_t *entry)
{
  entry_t *tmp = entry->next->next;
  free(entry->next);
  entry->next = tmp;
}

ioopm_hash_table_t *ioopm_hash_table_create()
{
  ioopm_hash_table_t *result = calloc(1, sizeof(ioopm_hash_table_t));
  return result;
}

static entry_t *find_previous_entry_for_key(entry_t *entry, int key)
{
  entry_t *cursor = entry;
  entry_t *store = NULL;
  
  while(cursor != NULL)
    {
      if(cursor->key == key && key != 0)
	{
	  return store;
	}
      store = cursor;
      cursor = cursor->next;
    }
  return entry;
}

void ioopm_hash_table_insert(ioopm_hash_table_t *ht, int key, char *value)
{
  int bucket = abs(key) % No_Buckets;
  
  entry_t *entry = find_previous_entry_for_key(&ht->buckets[bucket], key);
  entry_t *next = entry->next;
  
  if (next != NULL && next->key == key)
    {
      next->value = value;
    }
  else
    {
      entry->next = entry_create(key, value, next);
    }
}

bool ioopm_hash_table_lookup(ioopm_hash_table_t *ht, int key, char **result)
{
  entry_t *tmp = find_previous_entry_for_key(&ht->buckets[key % No_Buckets], key);
  entry_t *next = tmp->next;

  if (next && next->key == key)
    {
      *result = next->value;
      return true;
    }
  else
    {
      return false;
    }
}

bool ioopm_hash_table_remove(ioopm_hash_table_t *ht, int key, char **result)
{
  if(ioopm_hash_table_lookup(ht, key, result))
    {
      entry_t *pentry = find_previous_entry_for_key(&ht->buckets[key % No_Buckets], key);
      *result = pentry->next->value;
      entry_destroy(pentry);
      return true;
    }
  else
    {
      return false;
    }
}

static void test_next(entry_t *entry)
{
  if (entry != NULL)
    {
      test_next(entry->next);
    }
  free(entry);
}

void ioopm_hash_table_destroy(ioopm_hash_table_t *ht)
{
  for(int i = 0; i <= 16; i++)
    {
      test_next(ht->buckets[i].next);
    }
  free(ht);
}


int main(int argc, char *argv[])
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  char *result = NULL;
  
  ioopm_hash_table_insert(ht, 0, "hej");
  ioopm_hash_table_remove(ht, 0, &result);

  ioopm_hash_table_destroy(ht);
  return 0;
}


