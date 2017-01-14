#include <priority_queue.h>
#include <string.h>
#include <hash_table.h>

#define FREQ_SIZE (125)
#define NUM_OF_CHAR (27)
#define SHORT_SIZE (16)
typedef unsigned short ushort;
typedef struct code{
	char bits;
	int code;
}code_t;

int freq[FREQ_SIZE];
ushort bit_buffer = 0;
code_t leftovers = (code_t){0, 0};


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
	if( *bin_p == 0 ){
		*bin_p = (*bin_p << leftovers.bits) ^ leftovers.code;
		bit_buffer += leftovers.bits;
		leftovers = (code_t){0, 0};
	}
	if( bit_buffer + c.bits >= SHORT_SIZE ){
		ushort temp = bit_buffer + c.bits - SHORT_SIZE;
		leftovers.code = c.code & (1 << temp) - 1;
		leftovers.bits = temp;
		c.bits -= temp;
		c.code >>= temp;
	}
	*bin_p = (*bin_p << c.bits) ^ c.code;
	bit_buffer += c.bits;

	if( bit_buffer == SHORT_SIZE)
		return (bit_buffer = 0);
	return 1;
}

int output_bin(FILE* fp, code_t* codes, char* text, size_t size){
	ushort bin = 0, result;
	u_int i, a, cantor;
	h_table_t ht;
	alloc_h_table(&ht, 81);
	i = 0;while( i < FREQ_SIZE ){
		if( codes[i].bits != 0 ){
			a = codes[i].code + codes[i].bits;
			cantor = a*(a+1)/2 + codes[i].bits; /* Cantor Pairing function */
			printf("Char: %c, code-bits: %d-%d\n", i, codes[i].code, codes[i].bits);
			insert_h(&ht, cantor, i);
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

u_int find_code(h_table_t *ht, ushort* temp, ushort* temp_bits, code_t* c){
	ushort cantor, bits = 0, mask;
	do{
		++bits;
		mask = (c->code << bits) ^ *temp >> (SHORT_SIZE - bits);
		cantor = (mask+bits+c->bits)*(mask+bits+c->bits+1)/2 + bits + c->bits; /* Cantor Pairing function */
		/* printf("buffer: %d, bits: %d\n", mask, bits + c->bits); */
	}while( !check(ht, cantor) && bits < *temp_bits ); /* Debug this infinite bit thing */
	c->bits = bits;
	c->code = mask;
	*temp <<= bits;
	*temp_bits -= bits;
	return lookup(ht, cantor);
}

int decompress(FILE* fp, size_t l_size){
	ushort result, temp;
	short temp_bits;
	code_t c = (code_t) {0, 0};
	u_int size;
	h_table_t ht;
	alloc_h_table(&ht, 81);
	fread(&size, sizeof(u_int), 1, fp);
	fread(ht.hash_table, sizeof(h_node_t), 81, fp);
	size_t text_size = (l_size - ftell(fp))/2; /* Each block is 2 bytes */
	while( text_size ){
		fread(&temp, sizeof(ushort), 1, fp);
		temp_bits = SHORT_SIZE;
		/* printf("temp: %d\n", temp); */
		while( temp_bits > 0 ){
			result = find_code(&ht, &temp, &temp_bits, &c);
			if( result ){
				printf("%c",(char)result);
				c.code = 0;c.bits = 0;
			}
		}
		text_size--;
	}
	printf("\n");
	return 0;
}

void test(){
	ushort bin = 0, result;
	code_t c = (code_t){2, 2};
	construct_block(c, &bin);
	c = (code_t){2, 1};
	construct_block(c, &bin);
	c = (code_t){2, 3};
	construct_block(c, &bin);
	c = (code_t){4, 2};
	construct_block(c, &bin);
	c = (code_t){3, 0};
	construct_block(c, &bin);
	c = (code_t){2, 2};
	result = construct_block(c, &bin);
	printf("%d: %d\n",bin, result);
	c = (code_t){2, 3};
	result = construct_block(c, &bin);
	printf("%d: %d\n",bin, result);
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
