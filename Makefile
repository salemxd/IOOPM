hash_table: hash_table.c
	gcc -g -Wall hash_table.c hash_table.h -o hash_table
hash_test: hash_table_test.c
	gcc -ggdb -pedantic -Wall hash_table_test.c hash_table.c -o testis -lcunit
