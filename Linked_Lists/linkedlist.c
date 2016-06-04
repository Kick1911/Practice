#ifndef LINKED_C
#define LINKED_C

#include <stdlib.h>
#include <linkedlist.h>

static int append(linked_list_t* list, char data){
	node_t* temp;
	if( !(temp = malloc(sizeof(node_t))) )
		return 2;
	temp->data = data;
	temp->next = NULL;
	if(!list->head){
		list->head = temp;
		list->end = list->head;
		return 0;
	}
	node_t* end = list->end;
	end->next = temp;
	temp->prev = end;
	list->end = end->next;
	return 0;
}

static node_t* find(linked_list_t* list, char data){
	node_t* temp = list->head;
	node_t* end = list->end->next;
	while(temp != end && temp->data != data)
		temp = temp->next;
	if(temp->data == data)
		return temp;
	else
		return NULL;
}

static int remove_data(linked_list_t* list, char data){
	node_t* ptr;
	if( !(ptr = find(list,data)) )
		return 1;

	if( ptr->prev == NULL )
		list->head = ptr->next;
	else if( ptr->next == NULL )
		list->end = ptr->prev;
	else{
		ptr->next->prev = ptr->prev;
		ptr->prev->next = ptr->next;
	}
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
	remove_data(&list,'C');

	printf("DATA: %c\n",list.head->data);
	printf("DATA of end: %c\n",list.end->data);
	display_linked_list(&list);
	return 0;
}

#endif
