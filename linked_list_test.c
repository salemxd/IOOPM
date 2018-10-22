#include <string.h>
#include <stdbool.h>
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


bool compare(elem_t a, elem_t b)
{
	if (a.i == b.i)
	{
		return true;
	}
	return false;
}


void applyfunc(elem_t *a, elem_t *b)
{
	a->i = b->i;
}


void test_append(void)
{
	ioopm_list_t *list = ioopm_linked_list_create(NULL);
	
	elem_t element;
	element.i = 12;

	ioopm_linked_list_append(list, element);
	CU_ASSERT_TRUE(ioopm_linked_list_get(list, 0).i == 12);
	ioopm_linked_list_destroy(list);
}

void test_prepend(void)
{
	ioopm_list_t *list = ioopm_linked_list_create(NULL);
	
	elem_t element;
	element.i = 12;
	ioopm_linked_list_append(list, element);
	
	
	elem_t element2;
	element2.i = 11;
	ioopm_linked_list_prepend(list, element2);
	CU_ASSERT_TRUE(ioopm_linked_list_get(list, 0).i == 11);
	ioopm_linked_list_destroy(list);
}


void test_insert(void)
{
	ioopm_list_t *list = ioopm_linked_list_create(NULL);
	
	elem_t element;
	element.i = 12;
	ioopm_linked_list_append(list, element);
	
	
	elem_t element2;
	element2.i = 11;
	ioopm_linked_list_prepend(list, element2);

	elem_t element3;
	element3.i = 10;
	ioopm_linked_list_insert(list, 1, element3);
	ioopm_linked_list_insert(list, 2, element3);
	
	CU_ASSERT_TRUE(ioopm_linked_list_get(list, 1).i == 10);
	ioopm_linked_list_destroy(list);
}


void test_remove(void)
{
	ioopm_list_t *list = ioopm_linked_list_create(NULL);
	
	elem_t element;
	element.i = 12;
	ioopm_linked_list_append(list, element);
	
	
	elem_t element2;
	element2.i = 11;
	ioopm_linked_list_prepend(list, element2);

	elem_t element3;
	element3.i = 10;
	ioopm_linked_list_insert(list, 1, element3);
	ioopm_linked_list_remove(list, 1);
	CU_ASSERT_FALSE(ioopm_linked_list_get(list, 1).i == 10);
	ioopm_linked_list_destroy(list);
}

void test_contain(void)
{
	ioopm_list_t *list = ioopm_linked_list_create(compare);
	
	elem_t element;
	element.i = 12;
	ioopm_linked_list_append(list, element);
	
	
	elem_t element2;
	element2.i = 11;
	ioopm_linked_list_prepend(list, element2);

	elem_t element3;
	element3.i = 10;
	ioopm_linked_list_insert(list, 1, element3);
	CU_ASSERT_TRUE(ioopm_linked_list_contains(list, element3));
	ioopm_linked_list_destroy(list);
}


void test_size(void)
{
	ioopm_list_t *list = ioopm_linked_list_create(compare);
	
	elem_t element;
	element.i = 12;
	ioopm_linked_list_append(list, element);
	
	
	elem_t element2;
	element2.i = 11;
	ioopm_linked_list_prepend(list, element2);

	elem_t element3;
	element3.i = 10;
	ioopm_linked_list_insert(list, 1, element3);
	CU_ASSERT_TRUE(ioopm_linked_list_size(list) == 3);
	ioopm_linked_list_destroy(list);
}


void test_is_empty_clear(void)
{
	ioopm_list_t *list = ioopm_linked_list_create(compare);

	elem_t element;
	element.i = 12;
	ioopm_linked_list_append(list, element);
	
	
	elem_t element2;
	element2.i = 11;
	ioopm_linked_list_prepend(list, element2);

	elem_t element3;
	element3.i = 10;
	ioopm_linked_list_insert(list, 1, element3);
	
	ioopm_linked_list_clear(list);

	CU_ASSERT_TRUE(ioopm_linked_list_is_empty(list));
	ioopm_linked_list_destroy(list);
}

void test_any(void)
{
	ioopm_list_t *list = ioopm_linked_list_create(compare);
	
	elem_t element;
	element.i = 12;
	ioopm_linked_list_append(list, element);
	
	elem_t element2;
	element2.i = 11;
	ioopm_linked_list_prepend(list, element2);

	elem_t element3;
	element3.i = 10;
	ioopm_linked_list_insert(list, 1, element3);
	
	CU_ASSERT_TRUE(ioopm_linked_list_any(list , compare, element3));
		
	ioopm_linked_list_destroy(list);
}


void test_all(void)
{
	ioopm_list_t *list = ioopm_linked_list_create(compare);
	
	elem_t element;
	element.i = 12;
	ioopm_linked_list_append(list, element);
	
	elem_t element2;
	element2.i = 11;
	ioopm_linked_list_prepend(list, element2);

	elem_t element3;
	element3.i = 10;
	ioopm_linked_list_insert(list, 1, element3);
	
	CU_ASSERT_FALSE(ioopm_linked_list_all(list , compare, element3));
		
	ioopm_linked_list_destroy(list);
}

void test_apply_all(void)
{
	ioopm_list_t *list = ioopm_linked_list_create(compare);
	
	elem_t element;
	element.i = 12;

	ioopm_linked_list_append(list, element);
	
	elem_t element2;
	element2.i = 11;
	ioopm_linked_list_prepend(list, element2);

	elem_t element3;
	element3.i =  10;
	ioopm_linked_list_insert(list, 1, element3);
	
	CU_ASSERT_FALSE(ioopm_linked_list_all(list , compare, element3));

	
	ioopm_linked_list_destroy(list);
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
	    (NULL == CU_add_test(test_suite1, "test 1", test_append)) ||
	    (NULL == CU_add_test(test_suite1, "test 2", test_prepend)) ||
	    (NULL == CU_add_test(test_suite1, "test 3", test_insert)) ||
	    (NULL == CU_add_test(test_suite1, "test 4", test_remove)) || 
	    (NULL == CU_add_test(test_suite1, "test 5", test_contain)) || 
	    (NULL == CU_add_test(test_suite1, "test 6", test_size)) || 
	    (NULL == CU_add_test(test_suite1, "test 7", test_is_empty_clear)) || 
	    (NULL == CU_add_test(test_suite1, "test 8", test_any)) || 
	    (NULL == CU_add_test(test_suite1, "test 9", test_all)) || 
	    (NULL == CU_add_test(test_suite1, "test 10", test_apply_all)) 
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
