#ifndef NODE_H
#define NODE_H

typedef struct Node{
	char data;
	int freq;
	struct Node* left;
	struct Node* right;
} node;

#endif
