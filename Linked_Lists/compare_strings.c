#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <linkedlist.h>

int compare(linked_list_t* a, linked_list_t* b){
	node_t* temp_a = a->head;
	node_t* temp_b = b->head;
	while( temp_a && temp_b && temp_a->data == temp_b->data ){
		temp_a = temp_a->next;
		temp_b = temp_b->next;
	}

	if( temp_a && temp_b )
		return ( temp_a->data > temp_b->data ) ? 1 : -1;
	
	if( !temp_a && temp_b ) return -1;
	if( temp_a && !temp_b ) return 1;

	return 0;
}

int main(void){
	int i;
	char* str1 = "geeksa";
	char* str2 = "geeksb";
	char* str3 = "geeks";
	linked_list_t a;
	linked_list_t b;
	linked_list_t c;
	LINKED_LIST_INIT(a);LINKED_LIST_INIT(b);LINKED_LIST_INIT(c);
	i = 0;while( i < strlen(str1) )
		append(&a, str1[i++]);
	i = 0;while( i < strlen(str2) )
		append(&b, str2[i++]);
	i = 0;while( i < strlen(str3) )
		append(&c, str3[i++]);
	printf("Compare a and b: %d\n",compare(&a,&b));
	printf("Compare a and c: %d\n",compare(&a,&c));
	printf("Compare c and c: %d\n",compare(&c,&c));
	return 0;
}
