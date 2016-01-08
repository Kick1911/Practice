#ifndef NODE_H
#define NODE_H

struct Node{
	char data;
	int freq;
	struct Node* left;
	struct Node* right;
};

#endif
