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

struct Node* build_trie(heap_t* pq, int* array, struct Node* root){
	int i = 0;
	(*pq).h = ALLOC_HEAP(FREQ_SIZE);
	(*pq).N = 0;
	struct Node top, temp;
	while( i < FREQ_SIZE ){
		if(array[i] != 0){
			struct Node n;
			n.data = i;
			n.freq = array[i];
			n.left = NULL;
			n.right = NULL;
			insert(pq, &n);
		}
		i++;
	}

	node* left,* right,* n;
	while( (*pq).N > 1 ){
		right = (node*) malloc(sizeof(node*));
		left = (node*) malloc(sizeof(node*));
		n = (node*) malloc(sizeof(node*));
		printf("%x, %x\n", left, right);
		delMax(pq, right);
		delMax(pq, left);
		(*n).data = '\0';
		(*n).freq = (*left).freq + (*right).freq;
		(*n).left = left;
		(*n).right = right;
		/* printf("BEFORE. parent: %d, left: %d, right: %d\n",n.freq,(*n.left).freq,(*n.right).freq); */
		insert(pq, n);
		printf("AFTER. parent: %d, left: %d, right: %d\n",(*n).freq,(*(*n).left).freq,(*(*n).right).freq);
	}
	delMax(pq, root);
}

int build_code(char** codes, struct Node* parent, char s[]){
	if( (*parent).left != NULL && (*parent).right != NULL ){
		char right_buffer[80];
		char left_buffer[80];
		strcpy(left_buffer, s);
		strcpy(right_buffer, s);
		strcat(left_buffer,"0");
		strcat(right_buffer,"1");
		printf("%d\n",(*(*parent).right).freq);
		printf("Going Left\n");
		build_code(codes, (*parent).left, left_buffer);
		printf("Going right\n");
		build_code(codes, (*parent).right, right_buffer);
	}
	else{
		codes[(*parent).data] = s;
	}
}

void rec_traverse(struct Node* parent, int i){
	if( (*parent).left != NULL && (*parent).right != NULL && i < 10 ){
		printf("%d\n", (*parent).freq );
		rec_traverse((*parent).right, i);
		i++;
	}
	else{
		printf("Done!\n");
	}
}

int compress(char* buffer, int size){
	int i = 0;
	heap_t pq;
	while( i < size )
		freq[(int)buffer[i++]] += 1;
	display(freq);
	struct Node root, a;
	build_trie(&pq, freq, &root);
	a = *root.right;
	printf("END. parent: %d, left: %d, right: %d\n",a.freq,(*a.left).freq,(*a.right).freq);
	char* codes[FREQ_SIZE];
	build_code(codes, &root, "");
	printf("%s\n",codes['b']);
}

void test(){
	int i = 0;
	int array[8] = {15,13,80,51,40,40,60,120};
	heap_t heap;
	heap.h = ALLOC_HEAP(10);
	heap.N = 0;
	struct Node a, b;
	struct Node n;
	struct Node new_node;
	n.data = array[0];
	n.freq = 159;
	a.data = array[1];
	a.freq = 162;
	b.data = array[2];
	b.freq = 132;
	n.left = &a;
	n.right = &b;
	swap(n.left, n.right);
	printf("BEFORE. parent: %d, left: %d, right: %d\n",n.freq,(*n.left).freq,(*n.right).freq);
	insert(&heap, &n);
	delMax(&heap, &new_node);
	printf("AFTER. parent: %d, left: %d, right: %d\n",new_node.freq,(*new_node.left).freq,(*new_node.right).freq);
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
