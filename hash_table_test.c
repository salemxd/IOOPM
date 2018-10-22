#include <string.h>
#include <stdbool.h>
#include <stdlib.h>
#include "CUnit/Basic.h"
#include "hash_table.h"
//#include "common.h"

int init_suite(void)
{
	return 0;
}

int clean_suite(void)
{
	return 0;
}


int hashtest(elem_t x)
{
	return x.i;
}

bool compare(elem_t a, elem_t b)
{
	if (a.i == b.i)
	{
		return true;
	}
	return false;
}

bool applyfunc(elem_t key, elem_t value, void *extra)
{
	if(key.i == 3 && strcmp(value.p, "hej") == 0)
	{
		return true;
	}
	return false;
}


void change(elem_t *a, elem_t *b, void *extra)
{
	(*a).i = 10;
	(*b).s = "delete";

}

void test_hash_table_create(void)
{
	ioopm_hash_table_t *ht = ioopm_hash_table_create(hashtest, compare);
	elem_t noll;
	noll.i = 0;
	CU_ASSERT_TRUE(compare(ht->buckets[0].key, noll));
	ioopm_hash_table_destroy(ht);
}

void test_hash_table_insert(void)
{
	ioopm_hash_table_t *ht = ioopm_hash_table_create(hashtest, compare);

	elem_t element;
	element.s = "hej";

	elem_t tre;
	tre.i = 3;
	ioopm_hash_table_insert(ht, tre ,element);
	elem_t check;
	check.s = ht->buckets[3].next->value.s;
	CU_ASSERT_TRUE(compare(check, element));
	ioopm_hash_table_destroy(ht);
}

void test_lookup()
{

	ioopm_hash_table_t *ht = ioopm_hash_table_create(hashtest, compare);
	elem_t result;
	result.s = NULL;
	//char *result = NULL;
	elem_t i;
	i.i = 0;
	for ( i; i.i < 18; ++i.i) /// 18 is a bit magical 
	{
		CU_ASSERT_FALSE(ioopm_hash_table_lookup(ht, i, &result));
	}

	elem_t element;
	element.s = "hej";


	elem_t tre;
	tre.i = 3;
	ioopm_hash_table_insert(ht, tre,element);

	elem_t minus;
	minus.i = -1;
	CU_ASSERT_TRUE(ioopm_hash_table_lookup(ht, tre, &element));
	CU_ASSERT_FALSE(ioopm_hash_table_lookup(ht, minus, &result));
	ioopm_hash_table_destroy(ht);
}

void test_remove()
{

	ioopm_hash_table_t *ht = ioopm_hash_table_create(hashtest, compare);
	elem_t element;
	element.s = "hej";
	
	elem_t noll;
	noll.i = 0;
	ioopm_hash_table_insert(ht, noll,element);

	ioopm_hash_table_remove(ht, noll, &element);

	CU_ASSERT_FALSE(ioopm_hash_table_lookup(ht, noll, &element));
	ioopm_hash_table_destroy(ht);
}

void test_size_clear()
{	
	ioopm_hash_table_t *ht = ioopm_hash_table_create(hashtest, compare);

	elem_t element;
	element.s = "hej";

	elem_t element2;
	element2.s = "nej";
	
	elem_t tre;
	tre.i = 3;

	elem_t fyra;
	fyra.i = 4;

	ioopm_hash_table_insert(ht, tre ,element);
	ioopm_hash_table_insert(ht, fyra ,element2);
	CU_ASSERT_TRUE(ioopm_hash_table_size(ht));
	ioopm_hash_table_clear(ht);
	CU_ASSERT_TRUE(ioopm_hash_table_is_empty(ht));
	ioopm_hash_table_destroy(ht);
}

void test_keys()
{
	ioopm_hash_table_t *ht = ioopm_hash_table_create(hashtest, compare);

	elem_t element;
	element.s = "hej";

	elem_t element2;
	element2.s = "nej";	
	elem_t tre;
	tre.i = 3;

	elem_t fyra;
	fyra.i = 4;

	ioopm_hash_table_insert(ht, tre ,element);
	ioopm_hash_table_insert(ht, fyra ,element2);
	
	ioopm_list_t *keylist = ioopm_hash_table_keys(ht);
	
	CU_ASSERT_TRUE(ioopm_linked_list_size(keylist) == 2);
	
	ioopm_linked_list_destroy(keylist);
	ioopm_hash_table_destroy(ht);
}
void test_values()
{
	ioopm_hash_table_t *ht = ioopm_hash_table_create(hashtest, compare);

	elem_t element;
	element.s = "hej";

	elem_t element2;
	element2.s = "nej";	
	elem_t tre;
	tre.i = 3;

	elem_t fyra;
	fyra.i = 4;

	ioopm_hash_table_insert(ht, tre ,element);
	ioopm_hash_table_insert(ht, fyra ,element2);
	elem_t *values = ioopm_hash_table_values(ht);
	
	CU_ASSERT_TRUE(strcmp(values[0].p, "hej") == 0);	
	CU_ASSERT_TRUE(strcmp(values[1].p, "nej") == 0);	
		
	
	free(values);
	ioopm_hash_table_destroy(ht);	
}

void test_has_key()
{
	
	ioopm_hash_table_t *ht = ioopm_hash_table_create(hashtest, compare);

	elem_t element;
	element.s = "hej";

	elem_t element2;
	element2.s = "nej";	
	
	elem_t tre;
	tre.i = 3;

	elem_t fyra;
	fyra.i = 4;

	ioopm_hash_table_insert(ht, tre ,element);
	ioopm_hash_table_insert(ht, fyra ,element2);
	
	CU_ASSERT_TRUE(ioopm_hash_table_has_key(ht, tre)); //////////////
	ioopm_hash_table_destroy(ht);
}


void test_table_any()
{
	
	ioopm_hash_table_t *ht = ioopm_hash_table_create(hashtest, compare);

	elem_t element;
	element.s = "hej";

	elem_t element2;
	element2.s = "nej";	
	elem_t tre;
	tre.i = 3;

	elem_t fyra;
	fyra.i = 4;

	ioopm_hash_table_insert(ht, tre ,element);
	ioopm_hash_table_insert(ht, fyra ,element2);
	CU_ASSERT_TRUE(ioopm_hash_table_any(ht, applyfunc, NULL)); //////////////
	ioopm_hash_table_destroy(ht);

}

void test_table_all()
{
	
	ioopm_hash_table_t *ht = ioopm_hash_table_create(hashtest, compare);

	elem_t element;
	element.s = "hej";

	elem_t element2;
	element2.s = "nej";	
	elem_t tre;
	tre.i = 3;

	elem_t fyra;
	fyra.i = 4;

	ioopm_hash_table_insert(ht, tre ,element);
	ioopm_hash_table_insert(ht, fyra ,element2);

	CU_ASSERT_FALSE(ioopm_hash_table_all(ht, applyfunc, NULL)); //////////////////
	ioopm_hash_table_destroy(ht);
}

void test_table_apply_all()
{
	
	ioopm_hash_table_t *ht = ioopm_hash_table_create(hashtest, compare);

	elem_t element;
	element.s = "hej";

	elem_t element2;
	element2.s = "nej";	
	
	elem_t tre;
	tre.i = 3;

	elem_t fyra;
	fyra.i = 4;

	ioopm_hash_table_insert(ht, tre ,element);
	ioopm_hash_table_insert(ht, fyra ,element2);

	ioopm_hash_table_apply_to_all(ht, change, NULL);
	CU_ASSERT_TRUE(strcmp(ht->buckets[3].next->value.s, "delete") == 0);
	ioopm_hash_table_destroy(ht);
}
int main()
{
	CU_pSuite test_suite1 = NULL;

	if (CUE_SUCCESS != CU_initialize_registry())
		return CU_get_error();

	test_suite1 = CU_add_suite("Test Suite 1", init_suite, clean_suite);
	if (NULL == test_suite1)
	{
		CU_cleanup_registry();
		return CU_get_error();
	}

	if (
			(NULL == CU_add_test(test_suite1, "test 1", test_hash_table_create)) ||
			(NULL == CU_add_test(test_suite1, "test 2", test_hash_table_insert)) ||
			(NULL == CU_add_test(test_suite1, "test 3", test_lookup)) ||
			(NULL == CU_add_test(test_suite1, "test 4", test_remove)) ||	
			(NULL == CU_add_test(test_suite1, "test 5", test_size_clear)) ||
			(NULL == CU_add_test(test_suite1, "test 6", test_keys)) ||
			(NULL == CU_add_test(test_suite1, "test 7", test_values)) ||
			(NULL == CU_add_test(test_suite1, "test 8", test_has_key)) ||
			(NULL == CU_add_test(test_suite1, "test 9", test_table_any)) ||
			(NULL == CU_add_test(test_suite1, "test 10", test_table_all)) || 
			(NULL == CU_add_test(test_suite1, "test 11", test_table_apply_all)) 
	   )
	{
		CU_cleanup_registry();
		return CU_get_error();
	}

	CU_basic_set_mode(CU_BRM_VERBOSE);
	CU_basic_run_tests();
	CU_cleanup_registry();
	return CU_get_error();
}
