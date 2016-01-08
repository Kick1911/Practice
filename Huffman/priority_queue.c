/* priority_queue.c */

#include <priority_queue.h>

#ifdef HEAP_H

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
	(*pq).h[(*pq).N++] = *n;
	swim( (*pq).h, &((*pq).h[(*pq).N-1]) ); /* The Nth element */
	/* print_heap(pq); */
}

/* int insert_new_node(heap_t* pq, char d, int f, struct Node* n){
	struct Node* temp;
	(*temp).data = d;
	(*temp).freq = f;
	(*temp).next = n;
	insert(pq, temp);
} */

struct Node* delMax(heap_t* pq){
	if( (*pq).N == 0 ){ fprintf(stderr,"Failed to delete max from heap.\nThe heap is empty."); exit(1); }
	struct Node* start = (*pq).h;
	struct Node* end = &((*pq).h[--((*pq).N)]);
	swap( start, end );
	struct Node* max = end;
	sink(start, end);
	/* *end = NULL; I wish I could do this. */
	/* Maybe do a resizing */
	/* assert assert_heap() */
	return max;
}

/* Healper functions  */
int swim(struct Node* start, struct Node* child){
	struct Node* parent = parent_p(start, child);
	while( child > start && (*parent).data < (*child).data ){
		swap(child, parent);
		child = parent;
		parent = parent_p(start, child);
	}
}

int sink(struct Node* root, struct Node* end){
	struct Node* parent = root;
	struct Node* left_child = child(parent, parent);
	while( left_child + 1 < end ){
		if( left_child < end && (*left_child).data < (*(left_child+1)).data ) left_child++;
		if( (*parent).data > (*left_child).data ) break;
		swap(parent, left_child);
		parent = left_child;
		left_child = child(root, parent);
	}
}

void print_heap(heap_t* heap){
	int i = 0;
	struct Node* temp = (*heap).h;
	while( i < (*heap).N )
		printf("'%d' ",temp[i++].data);
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

#endif
