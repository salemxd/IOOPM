#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"
#include "common.h"
#include <stdbool.h>
#include <string.h>

struct link 
{
  elem_t element;
  link_t *next;
};

struct list
{
  link_t *first;
  link_t *last;
  cmpfunc cfunc;
};

struct iter
{
  link_t *current;
  ioopm_list_t *list;
};

typedef bool (*func)(elem_t, elem_t);
typedef void (*fun)(elem_t *, elem_t);

ioopm_list_iterator_t *ioopm_list_iterator(ioopm_list_t *list)
{
  ioopm_list_iterator_t *iterator = calloc(1, sizeof(ioopm_list_iterator_t));
  iterator->current = list->first;
  iterator->list = list;
  return iterator;
}

bool ioopm_iterator_has_next(ioopm_list_iterator_t *iter)
{
  return iter->current->next != NULL; 
}

elem_t ioopm_iterator_current(ioopm_list_iterator_t *iter)
{
  return iter->current->next->element;
}

bool ioopm_iterator_next(ioopm_list_iterator_t *iter, elem_t *content)
{
  if(ioopm_iterator_has_next(iter))
    {
      *content = iter->current->next->element;
      iter->current = iter->current->next;
      return true;
    }
  return false;
}

void ioopm_iterator_destroy(ioopm_list_iterator_t *iter)
{
  free(iter);
  
}

void ioopm_iterator_reset(ioopm_list_iterator_t *iter)
{
  iter->current = iter->list->first;
}

bool ioopm_iterator_remove(ioopm_list_iterator_t *iter, elem_t *content)
{
  link_t *to_remove = iter->current->next;
  if(!to_remove)
    {
      return false;
    }
  *content = to_remove->element;
  iter->current->next = to_remove->next;
  if(iter->current->next)
    {
      iter->list->last = iter->current;
    }
  free(to_remove);
  return true;
}

link_t *link_new(elem_t element, link_t *next)
{
  link_t *result = malloc(sizeof(link_t));

  if (result)
    {
      result->element = element;
      result->next = next;
    }

  return result;
}

void ioopm_iterator_insert(ioopm_list_iterator_t *iter, elem_t element)
{
  link_t *temp = iter->current->next;
  link_t *link =link_new(element, temp);
  iter->current->next = link;
  iter->current = link;
  link->next = temp;
  if(iter->current->next)
    {
      iter->list->last = iter->current;
    }
}

ioopm_list_t *ioopm_linked_list_create(cmpfunc cfunc)
{
  ioopm_list_t *list = calloc(1, sizeof(ioopm_list_t));
  link_t *link = calloc(1, sizeof(link_t));
  list->first = link;
  list->last = link;
  list->cfunc = cfunc;
  return list;
}


void ioopm_linked_list_append(ioopm_list_t *list, elem_t element)
{
  link_t *link = link_new(element, NULL);
  list->last->next = link;
  list->last = link;
}

void ioopm_linked_list_prepend(ioopm_list_t *list, elem_t element)
{
  link_t *link = link_new(element, list->first->next);
  list->first->next = link;
}

link_t *find_previous(ioopm_list_t *list, int index)
{
  link_t *link = list->first;
  for(int i = 0; i < index; i++)
    {
      link = link->next;
    }
  return link;
}

void ioopm_linked_list_insert(ioopm_list_t *list, int index, elem_t element)
{
  link_t *link = find_previous(list, index);
  link_t *insert = link_new(element, link->next);
  link->next = insert;
  if(link->next == NULL)
    {
      list->last = insert;
    } 
}

elem_t ioopm_linked_list_remove(ioopm_list_t *list, int index)
{
  link_t *link = find_previous(list, index);
  link_t *tmp = link->next->next;
  elem_t result = link->element;
  free(link->next);
  link->next = tmp;
  if(tmp == NULL)
    {
      list->last = tmp;
    }
  return result;
}

elem_t ioopm_linked_list_get(ioopm_list_t *list, int index)
{
  link_t *link = find_previous(list, index);
  return link->next->element;
}

int ioopm_linked_list_size(ioopm_list_t *list)
{
  int counter = 0;
  link_t *link = list->first->next;
  while(link)
    {
      counter++;
      link = link->next;
    }
  //free(link);
  return counter;
}

bool ioopm_linked_list_contains(ioopm_list_t *list, elem_t element)
{
  if(ioopm_linked_list_size(list) == 0)
    {
      return false;
    }
  link_t *link = list->first->next;
  for(int i = 0; i < ioopm_linked_list_size(list); i++)
    {
      if(list->cfunc(link->element, element))
	{
	  return true;
	}
      link = link->next;
    }
  return false;
}

bool ioopm_linked_list_is_empty(ioopm_list_t *list)
{
  if(ioopm_linked_list_size(list) == 0)
    {
      return true ;
    }
  return false;
}

void testnext(link_t *link)
{
  if(link->next != NULL)
    {
      testnext(link->next);
    }
  free(link);
}

void ioopm_linked_list_clear(ioopm_list_t *list)
{
  if(!ioopm_linked_list_is_empty(list))
    {
      testnext(list->first->next);
    }
  list->first->next = NULL;
  list->last = list->first;
}

void ioopm_linked_list_destroy(ioopm_list_t *list)
{
  ioopm_linked_list_clear(list);
  free(list->first);
  free(list);
}

bool ioopm_linked_list_all(ioopm_list_t *list, func function, elem_t x)
{
  link_t *link = list->first->next;
  
  for(int i = 0; i < ioopm_linked_list_size(list); i++)
    {
      if(!function(link->element, x))
	{
	  return false;
	}
      link = link->next;
    }
  return true;
}

bool ioopm_linked_list_any(ioopm_list_t *list, func function, elem_t x)
{
  link_t *link = list->first->next;
  if(link == NULL)
  {
  	return false;
  }
  for(int i = 0; i < ioopm_linked_list_size(list); i++)
    {
      	if(function(link->element, x))
	{
	  return true;
	}
      link = link->next;
    }
  return false;
}

void ioopm_linked_apply_to_all(ioopm_list_t *list, fun function, elem_t x)
{
  link_t *link = list->first->next;
  
  for(int i = 0; i < ioopm_linked_list_size(list); i++)
    {
      function(&(link->element), x);
      link = link->next;
    }
}



