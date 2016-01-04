#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include "LinkedList.c"

#define FREQ_SIZE (125)
#define NUM_OF_CHAR (27)
#define ALLOC_CHILDREN ((trie_t*)malloc(sizeof(int) * NUM_OF_CHAR)) 

int freq[FREQ_SIZE];

typedef struct trie{
	int name;
	struct trie* children;
} trie_t;

void display(int* array){
	int i = 0;
	while( i < FREQ_SIZE )
		printf("%d ",array[i++]);
	printf("\n");
}

int insert(trie_t* children, int i){
	trie_t* ptr = children;
	while( (*ptr).name != 0 ){ ptr++; }
	trie_t temp;
	temp.name = i;
	temp.children = ALLOC_CHILDREN;
	*ptr = temp;
	free(temp.children);
	printf("%d ",(*ptr).name);
}

int build_trie(trie_t tree, int* array){
	tree.name = '\0';
	tree.children = ALLOC_CHILDREN; /* I should know the size before hand  */
	int i = 0;
	while( i < FREQ_SIZE ){
		if( array[i++] != 0 ){
			insert(tree.children, i);
		}
	}
	printf("\n");
	free(tree.children);
}

int compress(char* buffer, int length){
	trie_t tree;
	int i = 0;
	while( i < length )
		freq[(int)buffer[i++]] += 1;
	freq['\n'] = 0;
	freq['\0'] = 0;
	freq[' '] = 0;
	display(freq);
	build_trie(tree, freq);
}

int main(int argc, char** argv){
	FILE* pfile;
	long l_size;
	char* buffer;
	size_t result;
	trie_t test;
	trie_t* ptr = &test;

	pfile = fopen("test.data","rb");
	if( pfile == NULL ){ fprintf(stderr,"File not found.\n"); exit(1);}

	fseek(pfile, 0, SEEK_END);
	l_size = ftell(pfile);
	rewind(pfile);
	buffer = malloc(sizeof(char) * l_size);
	if( buffer == NULL ){ fprintf(stderr,"Memory allocation failed.\n"); exit(1);}
	result = fread(buffer,1,l_size,pfile);
	if( result != l_size ){ fprintf(stderr,"Error reading in file.\n"); exit(1);}
	buffer[l_size] == '\0';
	printf("Done :D\n");

	compress(buffer, l_size);

	free(buffer);
	fclose(pfile);
	return 0;
}
