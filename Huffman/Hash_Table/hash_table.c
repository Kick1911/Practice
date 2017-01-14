#ifndef HASH_C
#define HASH_C
#include <hash_table.h>


char alloc_h_table(h_table_t* ht, size_t m){
	ht->size = 0;
	ht->hash_table = (h_node_t*) malloc(sizeof(h_node_t) * m);
	int i = 0;while( i < m ){
		ht->hash_table[i++] = (h_node_t){-1, 0};
	}
	M = m;
	return ht->hash_table != NULL;
}

/* CRC variant hash algorithm */
static u_int hash(u_int k){
	return k % M;
}

char insert_h(h_table_t* ht, u_int k, u_int v){
	u_int hk = hash(k);
	/* if( ht->size == M/2 )
		resize(ht, 2*M); */
	while( ht->hash_table[hk].key != -1 ){
		fprintf(stderr, "Collision!! hash: %d, k: %d, value: %d is already placed\n",
						hk, k, ht->hash_table[hk].value);
		collisions++;
		hk = (hk+1) % M;
	}
	ht->hash_table[hk] = (h_node_t){ k, v };
	ht->size++;
	return 0;
}

static void display(h_table_t* ht){
	int i = 0;while( i < M )
		printf("%d ",ht->hash_table[i++].value);
	printf("\n");
}

u_int lookup(h_table_t* ht, u_int k){
	u_int hk = hash(k);
	while( ht->hash_table[hk].key != -1 &&
			ht->hash_table[hk].key != k ){ /* This is a problem */
		hk = (hk+1) % M; /* Can be infinite if hash table is full */
	}
	return ht->hash_table[hk].value;
}

char check(h_table_t* ht, u_int k){
	u_int hk = hash(k);
	while( ht->hash_table[hk].key != -1 &&
			ht->hash_table[hk].key != k ){ /* This is a problem */
		hk = (hk+1) % M; /* Can be infinite if hash table is full */
	}
	return ht->hash_table[hk].key == k;
}

#ifdef STATIC
static
#endif
int main(void){
	u_int cantor;
	h_table_t ht;
	size_t s = 11;
	alloc_h_table(&ht, s);
	int start = 76;
	int j = start + s;
	int i = start; while( i < start + s ){
		cantor = (i+j)*(i+j+1)/2 + j; /* Cantor Pairing function */
		printf("%d-%d, cantor: %d\n", i, j, cantor);
		insert_h(&ht, cantor, i);
		i++; j--;
	}
	display(&ht);
	int a = 84, b =79;
	u_int ratio = (a+b)*(a+b+1)/2 + b;
	printf("Probing %d-%d: %d\n",a, b, lookup(&ht, cantor));
	printf("collisions: %d, percentage: %f\n", collisions, (double)collisions / (double)s);
	return 0;
}

#endif
