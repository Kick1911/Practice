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
		right = (node*) malloc(sizeof(node));
		left = (node*) malloc(sizeof(node));
		n = (node*) malloc(sizeof(node));
		printf("%x, %x\n", left, right);
		delMin(pq, right);
		delMin(pq, left);
		(*n).data = '\0';
		(*n).freq = (*left).freq + (*right).freq;
		(*n).left = left;
		(*n).right = right;
		/* printf("BEFORE. parent: %d, left: %d, right: %d\n",n.freq,(*n.left).freq,(*n.right).freq); */
		insert(pq, n);
		printf("AFTER. parent: %d, left: %d, right: %d\n",(*n).freq,(*(*n).left).freq,(*(*n).right).freq);
	}
	delMin(pq, root);
}

int construct_block(char* code, size_t len, unsigned short* bin_p){
	unsigned short bin = *bin_p;
	int limit = 1 << (sizeof(unsigned short) * 8), i = 0;

	while( i < len && bin << 1 < limit){
		if( code[i] == '1' ){
			bin <<= 1;
			bin++;
		}
		else if( code[i] == '0' ){
			bin <<= 1;
		}
		else{
			fprintf(stderr,"Corrupt code\n");
			exit(2);
		}
		i++;
	}

	*bin_p = bin;
	if( bin << 1 >= limit ){
		return 0;
	}
	return 1;
}

int output_bin(FILE* fp, char** codes, char* text){
	unsigned short bin, result;
	int i = 0;
	while( i < FREQ_SIZE ){
		fwrite(codes[i], sizeof(char), strlen(codes[i]), fp);
		i++;
	}
	printf("CODE FOR b %s\n",codes['b']);
	while( *text ){
		printf("%c",*text);
		if( !construct_block(codes[*text], strlen(codes[*text]), &bin) ){
			fwrite(&bin, sizeof(bin), 1, fp);
			bin = 0;
		}
		text++;
	}
	printf("\n");
}

int build_code(char** codes, struct Node* parent,char* str){
	if( (*parent).left != NULL && (*parent).right != NULL ){
		char* left = malloc(sizeof(char) * 40);
		char* right = malloc(sizeof(char) * 40);
		strcpy(left, str);
		strcpy(right, str);
		left[strlen(str)] = '0';
		right[strlen(str)] = '1';
		left[strlen(str)+1] = '\0';
		right[strlen(str)+1] = '\0';
		printf("Going Left\n");
		build_code(codes, (*parent).left, left);
		printf("Going right\n");
		build_code(codes, (*parent).right, right);
	}
	else{
		codes[(*parent).data] = str;
		printf("%c: %s, %x\n",(*parent).data, codes[(*parent).data], codes + (*parent).data);
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

	char* codes[FREQ_SIZE];
	i = 0;
	while( i < FREQ_SIZE )
		codes[i++] = "";
	build_code(codes, &root, "");

	a = *root.right;
	printf("END. parent: %d, left: %d, right: %d\n",a.freq,(*a.left).freq,(*a.right).freq);

	FILE* fp = fopen("compressed.huff","wb");
	output_bin(fp, codes, buffer);
	fclose(fp);
	free(pq.h);
	return 0;
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
	delMin(&heap, &new_node);
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
