#ifndef LINCKED_H
#define LINCKED_H
#include <stdio.h>
#define LINKED_LIST_INIT(list) (list.head = NULL)

typedef struct node{
	char data;
	struct node* next;
	struct node* prev;
}node_t;

typedef struct linked_list{
	struct node* head;
	struct node* end;
}linked_list_t;

static __inline__ node_t* head(linked_list_t* l){
	return l->head;
}

static __inline__ void display_linked_list(linked_list_t* list){
	node_t* start = list->head;
	node_t* end = list->end;
	while( start != end->next ){
		printf("%c",start->data);
		start = start->next;
	}
	printf("\n");
}

int append(linked_list_t*,char);

#endif
