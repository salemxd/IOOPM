#include <string.h>
#include <stdbool.h>
#include "CUnit/Basic.h"
#include "hash_table.h"

int init_suite(void)
{
  return 0;
}

int clean_suite(void)
{
  return 0;
}

void test_hash_table_create(void)
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  CU_ASSERT_TRUE(ht->buckets[0].key == 0);
  ioopm_hash_table_destroy(ht);
}

void test_hash_table_insert(void)
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  ioopm_hash_table_insert(ht, 0, "hej");
  CU_ASSERT_TRUE(strcmp(ht->buckets[0].next->value, "hej")==0);
  CU_ASSERT_TRUE(ht->buckets[0].next->key == 0);
  ioopm_hash_table_destroy(ht);
}

void test_lookup()
{
   ioopm_hash_table_t *ht = ioopm_hash_table_create();
   char *result = NULL;
   
   for (int i = 0; i < 18; ++i) /// 18 is a bit magical 
     {
       CU_ASSERT_FALSE(ioopm_hash_table_lookup(ht, i, &result));
     }
   CU_ASSERT_FALSE(ioopm_hash_table_lookup(ht, -1, &result));
   ioopm_hash_table_destroy(ht);
}
void test_remove()
{
  ioopm_hash_table_t *ht = ioopm_hash_table_create();
  char *result = NULL;
  
  ioopm_hash_table_insert(ht, 0, "hej");
  ioopm_hash_table_remove(ht, 0, &result);

  CU_ASSERT_FALSE(ioopm_hash_table_lookup(ht, 0, &result));
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
    (NULL == CU_add_test(test_suite1, "test 1", test_lookup)) ||
    (NULL == CU_add_test(test_suite1, "test 2", test_remove)) ||
    (NULL == CU_add_test(test_suite1, "test 3", test_hash_table_insert))
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
