#ifndef HASH_H
#define HASH_H
#include <sys/types.h>
#include <malloc.h>
#include <string.h>

typedef unsigned int u_int;
static u_int M;
static u_int collisions = 0;

typedef struct h_node{
	u_int key;
	u_int value;
}h_node_t;

typedef struct h_table{
	u_int size;
	h_node_t* hash_table;
}h_table_t;

char alloc_h_table(h_table_t*, size_t);

static void resize(h_table_t* ht, size_t m){
	printf("##### resizing #####\n");
	ht->hash_table = (h_node_t*) realloc(ht->hash_table, sizeof(h_node_t) * m);
	int i = m/2;while( i < m )
		ht->hash_table[i++].key = -1;
	M = m;
}
char insert_h(h_table_t*, u_int, u_int);
u_int lookup(h_table_t*, u_int);
char check(h_table_t*, u_int);
static u_int hash(u_int);

#endif
