#include <priority_queue.h>

int main(void){
	heap_t a;
	node* n;
	/* (*n).data = 'a';
	(*n).freq = 10;
	insert(&a,n); */
	int i = 0;
	while( i < 5 ){
		n = (node*)malloc(sizeof(node*));
		printf("%x\n",n);
		i++;
	}
	return 0;
}
