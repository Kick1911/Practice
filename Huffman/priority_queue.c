/* priority_queue.c */

#include <priority_queue.h>

#ifdef HEAP_H

void swap(struct Node* n1, struct Node* n2){
	struct Node temp = *n1;
	*n1 = *n2;
	*n2 = temp;
}

struct Node* mid_p(struct Node* start, struct Node* end){
	if( start + 1 == end )
		return start;
	int mid_index = ( (int)(end - start) /2);
	return &(start[mid_index]);
}

int insert(heap_t* pq, struct Node n){
	(*pq).h[(*pq).N++] = n;
	return swim( (*pq).h, &((*pq).h[(*pq).N-1]) ); /* The Nth element */
}

struct Node pop(heap_t pq){
	if ( pq.N == 0 ){
		fprintf(stderr,"Heap is empty.");
		exit(1);
	}
	swap( &(pq.h[0]), &(pq.h[pq.N-1]) );
	struct Node max = pq.h[--pq.N];
	sink(pq.h, 0); /* The first element */
	/* pq.h[pq.N + 1] = NULL; */
	return max;
}

/* Healper functions  */
int swim(struct Node* start, struct Node* end){
	struct Node* mid = mid_p(start, end);
	while( end > start && (*mid).data < (*end).data ){
		swap(end, mid);
		end = mid;
	}
	return 0;
}

int sink(struct Node* n, int i){
	
}

void print_heap(heap_t* heap){
	int i = 0;
	struct Node* temp = (*heap).h;
	while( i < (*heap).N )
		printf("'%c' ",temp[i++].data);
	printf("\n");
}

int main(void){
	int i = 0;
	int array[5] = {15,13,80,51,40};
	heap_t heap;
	heap.h = ALLOC_HEAP(10);
	heap.N = 0;

	while( i < 5 ){
		struct Node n;
		n.data = array[i];
		insert(&heap, n);
	}

	printf("Heap size: %d\n",heap.N);
	print_heap(&heap);
	return 0;
}

#endif
