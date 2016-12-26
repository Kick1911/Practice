#include <priority_queue.h>
#include <string.h>
#include <hash_table.h>

#define FREQ_SIZE (125)
#define NUM_OF_CHAR (27)
#define SHORT_SIZE (15)

int freq[FREQ_SIZE];

typedef unsigned short ushort;
typedef struct code{
	char bits;
	int code;
}code_t;

void display(int* array){
	int i = 0;
	while( i < FREQ_SIZE )
		printf("%d ",array[i++]);
	printf("\n");
}

struct Node* build_trie(heap_t* pq, int* array, struct Node* root){
	int i = 0;
	pq->h = ALLOC_HEAP(FREQ_SIZE);
	pq->N = 0;
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
	while( pq->N > 1 ){
		right = (node*) malloc(sizeof(node));
		left = (node*) malloc(sizeof(node));
		n = (node*) malloc(sizeof(node));
		printf("%x, %x\n", left, right);
		delMin(pq, right);
		delMin(pq, left);
		n->data = '\0';
		n->freq = left->freq + right->freq;
		n->left = left;
		n->right = right;
		/* printf("BEFORE. parent: %d, left: %d, right: %d\n",n.freq,n.left->freq,n.right->freq); */
		insert(pq, n);
		printf("AFTER. parent: %d, left: %d, right: %d\n",n->freq,(*n->left).freq,(*n->right).freq);
	}
	delMin(pq, root);
}

int construct_block(code_t c, ushort* bin_p){
	ushort bin = *bin_p;
	int limit = 1 << (sizeof(ushort) * 8);

	int i = c.bits, int_code = c.code;
	while( i >= 0 && (bin << 1) < limit){
		if( (int_code >> i) ^ 0 ){   /* Equals 1 */
			bin <<= 1;
			bin++;
		}
		else if( (int_code >> i) ^ 1 ) /* Equals 0 */
			bin <<= 1;
		else
			fprintf(stderr,"Corrupt code\n"),exit(2);
		i--;
	}

	*bin_p = bin;
	if( bin << 1 >= limit )
		return 0;
	return 1;
}

int output_bin(FILE* fp, code_t* codes, char* text, size_t size){
	ushort bin = 0, result;
	u_int i;
	h_table_t ht;
	alloc_h_table(&ht, 81);
	i = 0;while( i < FREQ_SIZE ){
		if( codes[i].bits != 0 ){
			u_int ratio = (u_int) (((double)codes[i].code / (double)codes[i].bits) * 1000);
			insert_h(&ht, ratio, i);
		}
		i++;
	}
	fwrite(&ht.size, sizeof(u_int), 1, fp);
	fwrite(ht.hash_table, sizeof(h_node_t), 81, fp);
	while( *text )
		if( !construct_block(codes[*text++], &bin) ){
			fwrite(&bin, sizeof(bin), 1, fp);
			bin = 0;
		}
}

int build_code(code_t* codes, struct Node* parent,int int_code, int bits){
	if( parent->left != NULL && parent->right != NULL ){
		printf("Going Left\n");
		build_code(codes, parent->left, int_code << 1, bits + 1);
		printf("Going right\n");
		build_code(codes, parent->right, (int_code << 1) + 1, bits + 1);
	}
	else{
		code_t temp = {bits, int_code};
		codes[parent->data] = temp;
		printf("%c: %d-%d, %x\n",parent->data, codes[parent->data].code, bits, codes + parent->data);
	}
}

int compress(char* buffer, size_t l_size){
	int i = 0;
	heap_t pq;
	while( i < l_size )
		freq[(int)buffer[i++]]++;
	display(freq);
	struct Node root, a;
	build_trie(&pq, freq, &root);

	code_t* c = (code_t*) malloc(sizeof(code_t) * FREQ_SIZE);
	memset(c, 0, FREQ_SIZE);
	build_code(c, &root, 0, 0);

	a = *root.right;
	printf("END. parent: %d, left: %d, right: %d\n",a.freq,(*a.left).freq,(*a.right).freq);

	FILE* fp = fopen("compressed.huff","wb");
	output_bin(fp, c, buffer, l_size);
	fclose(fp);
	free(pq.h);
	return 0;
}

int decompress(FILE* fp, size_t l_size){
	ushort bits, mask;
	u_int size, ratio, result;
	h_table_t ht;
	alloc_h_table(&ht, 81);
	fread(&size, sizeof(u_int), 1, fp);
	fread(ht.hash_table, sizeof(h_node_t), 81, fp);
	size_t text_size = (l_size - ftell(fp))/2; /* Each block is 2 bytes */
	while( !feof(fp) ){
		ushort temp;
		fread(&temp, sizeof(ushort), 1, fp);
		bits = 1;
		do{
			mask = 1;
			mask = (mask << bits) - 1 & temp >> (SHORT_SIZE - bits);
			ratio = (u_int) (((double)mask / (double)bits) * 1000);
			++bits; /* build buffer */
			/* temp <<= bits; */
		}while( !(result = lookup(&ht, ratio)) );
		printf("%c",(char)result);
	}
	printf("\n");
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

	pfile = fopen(argv[2],"rb");
	if( pfile == NULL ){ fprintf(stderr,"File not found.\n"); exit(1);}
	fseek(pfile, 0, SEEK_END);
	l_size = ftell(pfile);
	rewind(pfile);


	if( *argv[1] == 'd' )
		decompress(pfile, l_size);
	else{
		buffer = malloc(sizeof(char) * l_size);
		if( buffer == NULL ){ fprintf(stderr,"Memory allocation failed.\n"); exit(1);}
		result = fread(buffer,1,l_size,pfile);
		if( result != l_size ){ fprintf(stderr,"Error reading in file.\n"); exit(1);}
		buffer[l_size - 1] = '\0';
		printf("Done :D\n");
		compress(buffer, l_size);
		free(buffer);
	}

	fclose(pfile);
	return 0;
}
