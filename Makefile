hash_table: hash_table.c
	gcc -g -Wall hash_table.c hash_table.h linked_list.c linked_list.h -o hash_table
hash_test: hash_table_test.c
	gcc -ggdb -pedantic -Wall hash_table_test.c hash_table.c linked_list.c linked_list.h -o testis -lcunit
linked_test: linked_list_test.c
	gcc -ggdb -pedantic -Wall linked_list_test.c linked_list.c linked_list.h -o testis2 -lcunit
