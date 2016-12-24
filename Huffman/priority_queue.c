/* priority_queue.c */
#ifndef HEAP_C
#define HEAP_C

#include <priority_queue.h>

void swap(struct Node* n1, struct Node* n2){
	struct Node temp = *n1;
	*n1 = *n2;
	*n2 = temp;
}

struct Node* parent_p(struct Node* root, struct Node* child){
	if( root + 1 == child )
		return root;
	int index = ( (int)(child - root - 1) /2);
	return &(root[index]);
}

struct Node* child(struct Node* root, struct Node* parent){
	int index = (2 * (int)(parent - root)) + 1;
	return &(root[index]);
}

int insert(heap_t* pq, struct Node* n){
	struct Node* ptr = pq->h + pq->N;
	*ptr = *n;
	/* printf("Has right: %d, left: %d\n",(*(*ptr).right).freq, (*(*ptr).left).freq); */
	pq->N++;
	swim( pq->h, pq->h + pq->N - 1 ); /* The Nth element */
}

int delMin(heap_t* pq, struct Node* n){
	if( (*pq).N == 0 ){ fprintf(stderr,"Failed to delete min from heap.\nThe heap is empty."); exit(1); }
	struct Node* start = (*pq).h;
	struct Node* end = &((*pq).h[--((*pq).N)]);
	swap( start, end );
	*n = *end;
	sink(start, end - 1);
	/* *end = NULL; I wish I could do this. */
	/* Maybe do a resizing */
	/* assert assert_heap() */
	return 0;
}

/* Healper functions  */
int swim(struct Node* start, struct Node* child){
	struct Node* parent = parent_p(start, child);
	while( child > start && (*parent).freq > (*child).freq ){
		swap(child, parent);
		child = parent;
		parent = parent_p(start, child);
	}
}

int sink(struct Node* root, struct Node* end){
	struct Node* parent = root;
	struct Node* left_child = child(root, parent);
	while( left_child  <= end ){
		if( left_child < end && (*left_child).freq > (*(left_child+1)).freq ) left_child++;
		if( (*parent).freq < (*left_child).freq ) break;
		swap(parent, left_child);
		parent = left_child;
		left_child = child(root, parent);
	}
}

void print_heap(heap_t* heap){
	int i = 0;
	if( (*heap).N == 0 ) printf("Heap is Empty.\n");
	struct Node* temp = (*heap).h;
	while( i < (*heap).N )
		printf("'%d' ",temp[i++].freq);
	printf("\n");
}

/* int main(void){
	int i = 0;
	int array[8] = {15,13,80,51,40,40,60,120};
	heap_t heap;
	heap.h = ALLOC_HEAP(10);
	heap.N = 0;

	while( i < 8 ){
		struct Node* n1 = (struct Node*)malloc(sizeof(void*));
		(*n1).data = array[i++];
		insert(&heap, n1);
	}

	while( heap.N > 0 ){
		delMax(&heap);
		print_heap(&heap);
	}

	printf("Heap size: %d\n",heap.N);
	return 0;
} */

#endif /* End of HEAP_C */
