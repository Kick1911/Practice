/* linked.h */

struct Node{
    char data;
    struct Node* next;
};

typedef struct linked_list{
	struct Node* head;
} linked_list_t;

void display_linked_list(linked_list_t);
