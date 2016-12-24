INCLUDE=../include
LIB=../lib

hash_table: hash_table.h hash_table.c
	gcc -ansi -g -o hash_table -I$(INCLUDE) hash_table.c
library: hash_table.h hash_table.c
	gcc -ansi -D STATIC -c -o hash_table.o -I$(INCLUDE) hash_table.c
	ar -cvq $(LIB)/libhash.a *.o
	rm -f hash_table.o
clean:
	rm -f hash_table
