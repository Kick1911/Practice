#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>
#include <linked.h>

#define FREQ_SIZE (125)
#define NUM_OF_CHAR (27)

int freq[FREQ_SIZE];

void display(int* array){
	int i = 0;
	while( i < FREQ_SIZE )
		printf("%d ",array[i++]);
	printf("\n");
}

int build_trie(int* array){
	int i = 0;
	linked_list_t list;
	struct Node top, temp;
	list.head = &top;
	top.data = '\0';
	struct Node* ptr = list.head;
	while( i < FREQ_SIZE ){
		if( array[i] != 0 ){
			temp.data = i;
			(*ptr).next = &temp;
			printf("%c ",(*(*ptr).next).data);
		}
		i++;
	}
	printf("\n");
	/* display_linked_list(list); */
}

int compress(char* buffer, int length){
	int i = 0;
	while( i < length )
		freq[(int)buffer[i++]] += 1;
	freq['\n'] = 0;
	freq['\0'] = 0;
	freq[' '] = 0;
	display(freq);
	build_trie(freq);
}

void test(){
	linked_list_t l;
	struct Node a;
	l.head = &a;
	struct Node b;
	a.data = 'k';
	b.data = 'i';
	a.next = &b;
	int i = 1; while( i < 10 ){
		struct Node temp;
		temp.data = i++;
		printf("%d ",temp.data);
	}
	struct Node* ptr = l.head;
	printf("%c\n",(*ptr).data);
	printf("%c\n",(*(*ptr).next).data);
}

int main(int argc, char** argv){
	FILE* pfile;
	long l_size;
	char* buffer;
	size_t result;

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
