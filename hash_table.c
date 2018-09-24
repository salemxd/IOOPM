#include <stdio.h>
#include <stdlib.h>
#include "hash_table.h"

static entry_t *entry_create(int key, char *value, entry_t *next)
{
  entry_t *new_entry = calloc(1, sizeof(entry_t));
  new_entry->key = key;
  new_entry->value = value;
  new_entry->next = next;
  return new_entry;
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
      if(cursor->key == key)
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
  int bucket = key % 17;
  
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

void testcase1()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  ioopm_hash_table_insert(ht, 17, "one");
  ioopm_hash_table_insert(ht, 34, "two");
  ioopm_hash_table_insert(ht, 34, "three");
  ioopm_hash_table_insert(ht, 51, "four");
  printf("%s\n", ht->buckets[0].next->value);
  printf("%s\n", ht->buckets[0].next->next->value);
  printf("%s\n", ht->buckets[0].next->next->next->value);
}

int main(int argc, char *argv[])
{
  //testcase1();
  return 0;
}
