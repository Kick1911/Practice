#include <priority_queue.h>
#include <string.h>

#define FREQ_SIZE (125)
#define NUM_OF_CHAR (27)

int freq[FREQ_SIZE];

void display(int* array){
	int i = 0;
	while( i < FREQ_SIZE )
		printf("%d ",array[i++]);
	printf("\n");
}

struct Node* build_trie(heap_t* pq, int* array){
	int i = 0;
	(*pq).h = ALLOC_HEAP(FREQ_SIZE);
	(*pq).N = 0;
	struct Node top, temp;
	while( i < FREQ_SIZE ){
		if(array[i] != 0){
			struct Node n;
			n.data = i;
			n.freq = array[i];
			insert(pq, &n);
		}
		i++;
	}

	print_heap(pq);
	while( (*pq).N > 1 ){
		struct Node* left = delMax(pq);
		struct Node* right = delMax(pq);
		struct Node n;
		n.data = '\0';
		n.freq = (*left).freq + (*right).freq;
		n.left = left;
		n.right = right;
		insert(pq, &n);
	}
	return delMax(pq);
}

int build_code(char** codes, struct Node* parent, char* s){
	struct Node* left = (*parent).left;
	struct Node* right = (*parent).right;
	if( (*left).data != 0 && (*right).data != 0 ){
		char right_buffer[80];
		char left_buffer[80];
		strcpy(left_buffer, s);
		strcpy(right_buffer, s);
		strcat(right_buffer,"1");
		strcat(left_buffer,"0");
		build_code(codes, left, left_buffer);
		build_code(codes, right, right_buffer);
	}
	else{
		codes[(*parent).data] = s;
	}
}

int compress(char* buffer, int size){
	int i = 0;
	heap_t pq;
	while( i < size )
		freq[(int)buffer[i++]] += 1;
	display(freq);
	struct Node* root = build_trie(&pq, freq);
	char* codes[FREQ_SIZE];
	build_code(codes, root, "");
}

void test(){
	int i = 0;
	int array[8] = {15,13,80,51,40,40,60,120};
	heap_t heap;
	heap.h = ALLOC_HEAP(10);
	heap.N = 0;
	struct Node n1;
	n1.data = array[0];
	insert(&heap, &n1);
	print_heap(&heap);
	free(heap.h);
}

int main(int argc, char** argv){
	FILE* pfile;
	long l_size;
	char* buffer;
	size_t result;

	pfile = fopen(argv[1],"rb");
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
