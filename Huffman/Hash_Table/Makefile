INCLUDE=../include
LIB=../lib

hash_table: hash_table.h hash_table.c
	gcc -ansi -g -o hash_table -I$(INCLUDE) hash_table.c
library: hash_table.h hash_table.c
	gcc -ansi -D STATIC -fPIC -c -o hash_table.o -I$(INCLUDE) hash_table.c
	gcc -ansi -shared -o $(LIB)/libhash.so.1 hash_table.o
	rm -f hash_table.o
clean:
	rm -f hash_table
