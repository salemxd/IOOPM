#include <stdio.h>
#include <stdlib.h>
#include "hash_table.h"
#include <stdbool.h>
#include <string.h>
#include "common.h"

#define No_Buckets 17

static entry_t *entry_create(elem_t key, elem_t value, entry_t *next)
{
  entry_t *new_entry = calloc(1, sizeof(entry_t));
  new_entry->key = key;
  new_entry->value = value;
  new_entry->next = next;
  return new_entry;
}

void entry_destroy(entry_t *entry)
{
  free(entry);
}

ioopm_hash_table_t *ioopm_hash_table_create(hash_func func1, cmpfunc func2, cmpfunc func3)
{
  ioopm_hash_table_t *result = calloc(1, sizeof(ioopm_hash_table_t));
  return result;
}

static entry_t *find_previous_entry_for_key(ioopm_hash_table_t *ht, entry_t *entry, elem_t key)
{
  entry_t *cursor = entry;
  entry_t *store = NULL;

  while(cursor != NULL)
    {
      if(ht->cfunc(cursor->key, key))
	{
	  return store;
	}
      store = cursor;
      cursor = cursor->next;
    }
  return entry;
}

void ioopm_hash_table_insert(ioopm_hash_table_t *ht, elem_t key, elem_t value)
{
  int bucket = abs(ht->hfunc(key)) % No_Buckets;
  entry_t *entry = find_previous_entry_for_key(ht,&ht->buckets[bucket], key);
  entry_t *next = entry->next;

  if (next != NULL && ht->cfunc(next->key, key))
    {
      next->value = value;
    }
  else
    {
      entry->next = entry_create(key, value, next);
      ht->ht_size += 1;
    }
}

bool ioopm_hash_table_lookup(ioopm_hash_table_t *ht, elem_t key, elem_t *result)
{
  entry_t *tmp = find_previous_entry_for_key(ht,&ht->buckets[abs(ht->hfunc(key)) % No_Buckets], key);
  entry_t *next = tmp->next;

  if (next && ht->cfunc(next->key, key))
    {
      *result = next->value;
      return true;
    }
  else
    {
      return false;
    }
}

bool ioopm_hash_table_remove(ioopm_hash_table_t *ht, elem_t key, elem_t *result)
{
  if(ioopm_hash_table_lookup(ht, key, result))
    {
      entry_t *pentry = find_previous_entry_for_key(ht,&ht->buckets[abs(ht->hfunc(key)) % No_Buckets], key);
      *result = pentry->next->value;

      entry_t *tmp = pentry->next->next;
      entry_destroy(pentry->next);
      
      pentry->next = tmp;
      ht->ht_size -= 1;

      return true;
    }
  else
    {
      return false;
    }
}

void ioopm_hash_table_clear(ioopm_hash_table_t *ht)
{		
  if (ht)
    {
      entry_t *tmp = NULL;
      for(int i = 0; i <= 16; i++)
	{		
	  entry_t *del = ht->buckets[i].next;
	  ht->buckets[i].next = NULL;

	  while(del != NULL)
	    {
	      tmp = del->next;
	      entry_destroy(del);
	      del = tmp;
	      ht->ht_size -= 1;
	    }
	}
    }
}

void ioopm_hash_table_destroy(ioopm_hash_table_t *ht)
{
  ioopm_hash_table_clear(ht);
  free(ht);
}

int ioopm_hash_table_size(ioopm_hash_table_t *ht)
{
  return ht->ht_size;
}

bool ioopm_hash_table_is_empty(ioopm_hash_table_t *ht)
{
  return ioopm_hash_table_size(ht) == 0;
}


ioopm_list_t *ioopm_hash_table_keys(ioopm_hash_table_t *ht)
{
  ioopm_list_t *list = ioopm_linked_list_create();
  for(int i = 0; i <= 16; i++)
    {
      entry_t *entry = &ht->buckets[i];
      while(entry->next)
	{
	  ioopm_linked_list_append(list, entry->next->key);
	}
    }
  return list;
}

elem_t *ioopm_hash_table_values(ioopm_hash_table_t *ht)
{
  elem_t *counter = calloc(ioopm_hash_table_size(ht), sizeof(elem_t));
  int pekare = 0;

  for(int i = 0; i <= 16; i++)
    {
      entry_t *entry = &ht->buckets[i];
      while(entry->next != NULL)
	{
	  counter[pekare] = entry->next->value;
	  pekare++;
	  entry = entry->next;
	}
    }
  return counter;
}
bool ioopm_hash_table_has_value(ioopm_hash_table_t *ht, elem_t value)
{
  elem_t *list = ioopm_hash_table_values(ht);
  for(int i = 0; i < ioopm_hash_table_size(ht); i++)
    {
      if(ht->cfunc(list[i], value)==0)
	{
	  return true;
	}
    }
  return false;
}
bool ioopm_hash_table_has_key(ioopm_hash_table_t *ht, elem_t key)
{

  ioopm_list_t *list = ioopm_hash_table_keys(ht);
  ioopm_list_iterator_t *iterator = ioopm_list_iterator(list);
  for(int i = 0; i < ioopm_hash_table_size(ht); i++)
    {
      elem_t hej = ioopm_iterator_current(iterator);
      if(ht->cfunc(hej, key))
	{
	  return true;
	}

      ioopm_iterator_next(iterator, NULL);
    }
  return false;
}

bool ioopm_hash_table_any(ioopm_hash_table_t *ht, ioopm_apply_function function, void *x)
{
  ioopm_list_t *list = ioopm_hash_table_keys(ht);
  ioopm_list_iterator_t *iterator = ioopm_list_iterator(list);
  elem_t *strings = ioopm_hash_table_values(ht);

  for(int i = 0; i <= ioopm_hash_table_size(ht); i++)
    {
      if(function(ioopm_iterator_current(iterator), strings[i], x))
	{
	  return true; 
	}
      ioopm_iterator_next(iterator, NULL);
    }
  return false;
}

void ioopm_hash_table_apply_to_all(ioopm_hash_table_t *ht, ioopm_apply_function function, void *x)
{
  for(int i = 0; i <= ioopm_hash_table_size(ht); i++)
    {
      entry_t *entry = ht->buckets[i].next;
      while(entry->next != NULL)
	{
	  function(entry->key, entry->value, x);
	  entry = entry->next;
	}
    }
}

bool ioopm_hash_table_all(ioopm_hash_table_t *ht, ioopm_apply_function function, void *x)
{
  ioopm_list_t *list = ioopm_hash_table_keys(ht);
  ioopm_list_iterator_t *iterator = ioopm_list_iterator(list);
  elem_t *values = ioopm_hash_table_values(ht);

  for(int i = 0; i <= ioopm_hash_table_size(ht); i++)
    {
      if(!function(ioopm_iterator_current(iterator), values[i], x))
	{
	  return false; 
	}
      ioopm_iterator_next(iterator, NULL);
    }
  return true;
}

int main(int argc, char *argv[])
{ 
  
  return 0;
}

