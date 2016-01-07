#include <stdio.h>
#include <linked.h>

void display_linked_list(linked_list_t n){
	struct Node* temp;
	temp = n.head;
	printf("%c\n",(*temp).data);
	while( (*temp).next != NULL ){
		printf("%c\n",(*temp).data);
		temp = (*temp).next;
	}
}

/* int main(){
	linked_list_t l;
	struct Node a;
	l.head = &a;
	struct Node b;
	a.data = 'k';
	b.data = 'i';
	a.next = &b;
	struct Node* ptr = l.head;
	printf("%c\n",(*ptr).data);
	printf("%c\n",(*(*ptr).next).data);
	return 0;
} */
