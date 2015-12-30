#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define FREQ_SIZE (60)
#define NUM_OF_CHAR (10)
int freq[FREQ_SIZE];
typedef struct trie{
	int name;
	struct trie* children;
} trie_t;

int build_trie(trie_t tree, int* array){
	tree.name = '\0';
	tree.children = (int)malloc(sizeof(int) * NUM_OF_CHAR); /* I should know the size before hand  */
	int i = 0;
	while( i < FREQ_SIZE ){
		if( array[i] != 0 ){
			insert(i);
		}
	}
}

int compress(char* buffer){
	trie_t tree;
	int i = 0;
	while(buffer[i])
		freq[buffer[i++]] += 1;
	build_trie(tree, freq);
}

int main(int argc, char** argv){
	FILE* pfile;
	long l_size;
	char* buffer;
	size_t result;

	pfile = fopen("/home/kick/Documents/array.data","rb");
	if( pfile == NULL ){ fprintf(stderr,"File not found.\n"); exit(1);}

	fseek(pfile, 0, SEEK_END);
	l_size = ftell(pfile);
	rewind(pfile);
	buffer = (char*)malloc(sizeof(char) * l_size);
	if( buffer == NULL ){ fprintf(stderr,"Memory allocation failed.\n"); exit(1);}
	result = fread(buffer,1,l_size,pfile);
	if( result != l_size ){ fprintf(stderr,"Error reading in file.\n"); exit(1);}
	buffer[l_size] == '\0';
	printf("Done :D\n");
	compress(buffer);

	fclose(pfile);
	free(buffer);
	return 0;
}
