#ifndef HASH_C
#define HASH_C
#include <hash_table.h>


char alloc_h_table(h_table_t* ht, size_t m){
	ht->size = 0;
	ht->hash_table = (h_node_t*) malloc(sizeof(h_node_t) * m);
	int i = 0;while( i < m )
		ht->hash_table[i++].key = -1;
	M = m;
	return ht->hash_table != NULL;
}

/* CRC variant hash algorithm */
u_int hash(u_int k){
	/* u_int highorder = h & 0xf8000000;
	h <<= 5;
	h ^= highorder >> 27;
	h = (h ^ k) % M; */
	return k % M;
}

char insert(h_table_t* ht, u_int k, u_int v){
	/* double ratio = ((double)k / (double)l) * 1000; */
	u_int hk = hash(k);
	/* printf("%d-%d, ratio: %d\n", k, l, (int)ratio); */
	if( ht->size == M/2 )
		resize(ht, 2*M);
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

u_int lookup(h_table_t* ht, u_int k){
	u_int hk = hash(k);
	while( ht->hash_table[hk].key != k && (hk++) % M );
	return ht->hash_table[hk].value;
}

void display(h_table_t* ht){
	int i = 0;while( i < M )
		printf("%d ",ht->hash_table[i++].value);
	printf("\n");
}

int main(void){
	h_table_t ht;
	size_t s = 11;
	alloc_h_table(&ht, s);
	int start = 76;
	int j = start + s;
	int i = start; while( i < start + s ){
		double ratio = ((double)i / (double)j) * 1000;
		insert(&ht, ratio, i);
		i++; j--;
	}
	display(&ht);
	int a = 84, b =79;
	double ratio = ((double)a / (double)b) * 1000;
	printf("Probing %d-%d: %d\n",a, b, lookup(&ht, ratio));
	printf("collisions: %d, percentage: %f\n", collisions, (double)collisions / (double)s);
	return 0;
}

#endif
