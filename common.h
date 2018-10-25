#pragma once
#include <stdbool.h>

/// @brief an union to handle arbitrary data
typedef union elem elem_t;

union elem
{
		int i;
		unsigned int u;
		bool b;
		float f;
		void *p;
		char *s;
};

/// @brief functions to handle arbitrary data in the program.
typedef int(*hash_func)(elem_t key);
typedef bool(*cmpfunc)(elem_t a, elem_t b);
typedef struct link link_t;
