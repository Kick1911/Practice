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
	/* (*n).data = 'a';
	(*n).freq = 10;
	insert(&a,n); */
	char* texts[5];
	/* char j[] = "j";
	char buffer[40];
	strcpy(buffer, texts[0]); */
	test(texts, "", 0);
	/* display(texts, 5); */
	printf("1: %s\n",texts[1]);
	/* while( i < 5 ){
		n = (node*)malloc(sizeof(node*));
		printf("%x\n",n);
		i++;
	} */
	return 0;
}
