#include <priority_queue.h>
#include <string.h>

void test(char** texts, char* str, int i){
	if( i < 5 ){
		char buffer[40];
		strcpy(buffer, str);
		buffer[strlen(str)] = 'a' + i;
		buffer[strlen(str) + 1] = '\0';
		printf("%s ", buffer);
		test(texts, buffer, i+1);
	}
	else{
		texts[0] = str;
		texts[1] = str;
		printf("%s\n", texts[0]);
	}
}

void display(char** texts, int len){
	int i = 0;
	while( i < len )
		printf("%s\n",texts[i++]);
}

int main(void){
	heap_t a;
	node* n;
	char* codes[125];
	FILE* fp = fopen("compressed.huff","rb");
	if( fp != NULL )
		fread(codes, sizeof(char*), 125, fp);
	else
		fprintf(stderr,"Error in read.\n");
	printf("%s\n",codes['b']);
	return 0;
}
