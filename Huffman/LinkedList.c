#include <stdio.h>

int length = 0;

struct Node{
	char data;
	struct Node* next;
};

typedef struct linked_list{
	struct Node* head;
	struct Node* next = (*head).next;
} linked_list_t;


void display_link_list(struct linked_list* n){
	while( (*n).data != 0 ){
		printf("%s\n",(*n).data);
		n = (*n).next;
	}
}
