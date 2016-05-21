#ifndef LINKED_C
#define LINKED_C

#include <stdlib.h>
#include <linkedlist.h>

static int append(linked_list_t* list, char data){
	node_t* temp = malloc(sizeof(node_t));
	temp->data = data;
	temp->next = NULL;
	if(!list->head){
		list->head = temp;
		list->end = list->head;
		return 0;
	}
	node_t* end = list->end;
	end->next = temp;
	list->end = end->next;
	return 0;
}

int main(void){
	linked_list_t list;
	LINKED_LIST_INIT(list);
	printf("sizeof list %d\n",sizeof(list));
	printf("sizeof node_t %d\n",sizeof(node_t));
	printf("sizeof linked_list_t %d\n",sizeof(linked_list_t));
	
	append(&list, 'A');
	append(&list, 'B');
	append(&list, 'C');

	printf("DATA: %c\n",list.head->data);
	printf("DATA of next: %c\n",list.head->next->data);
	display_linked_list(&list);
	return 0;
}

#endif
