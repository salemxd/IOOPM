#pragma once
#include <stdbool.h>

typedef union elem elem_t;

union elem
{
  int i;
  unsigned int u;
  bool b;
  float f;
  void *p;
};

typedef int(*hash_func)(elem_t key);
typedef bool(*cmpfunc)(elem_t a, elem_t b);
