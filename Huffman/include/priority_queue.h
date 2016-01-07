/* priority_queue.h */
#include <stdio.h>
#include <stdlib.h>
#include <linked.h>

#ifndef HEAP_H
#define HEAP_H

#define ALLOC_HEAP(X) ((struct Node*)malloc(sizeof(int) * X))

typedef struct heap{
	struct Node* h;
	int N;
} heap_t;

void swap(struct Node*, struct Node*);

#endif
