/* priority_queue.h */
#include <stdio.h>
#include <stdlib.h>
#include <node.h>

#ifndef HEAP_H
#define HEAP_H

#define ALLOC_HEAP(X) ((struct Node*)malloc(sizeof(int) * X))

typedef struct heap{
	struct Node* h;
	int N;
} heap_t;

void print_heap(heap_t*);
int insert(heap_t*, struct Node*);
int insert_new_node(heap_t*, char, int, struct Node*);
struct Node* delMax(heap_t*);

#endif
