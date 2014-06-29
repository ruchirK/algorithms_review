#include <stdio.h>
#include <stdlib.h>

struct node {
	void* data;
	struct node* next;
};

struct linked_list {
	struct node* head;
	struct node* tail;
};

struct linked_list* init_single_linked_list(){
	struct linked_list* list = (struct linked_list*) malloc(sizeof(struct linked_list));
	if(list == NULL) {
		return (struct linked_list*)  NULL;
	}
	list->head = NULL;
	list->tail = NULL;
	return list;
}
	
struct node* make_single_linked_node(void* value) {
	struct node* new_node = (struct node* ) malloc(sizeof (struct node));
	if (new_node == NULL){
		//perror("");
		return (struct node *) NULL;
	}
	new_node->data = value;
	new_node->next = NULL;
	return new_node;
}
	
int insert_head_single_linked_list(struct linked_list* list, void* value){
	if (list == NULL){
		fprintf(stderr, "ERROR: Linked list uninitialized\n");
		return -1;
	}
	struct node* new_node;
	new_node = make_single_linked_node(value);
	if (new_node == NULL) {
		return -1;
	}
	new_node->next = list->head;
	list->head = new_node;
	if(list->tail == NULL) {
		list->tail = new_node;
	}
	return 0;
}

int insert_tail_single_linked_list(struct linked_list* list, void* value){
	if (list == NULL) {
		return -1;
	}
	if (list->head == NULL && list->tail == NULL) {
		return insert_head_single_linked_list(list,  value);
	}
	if(list->tail == NULL) {
		return -1;
	}
	struct node* new_node;
	new_node = make_single_linked_node(value);
	if (new_node == NULL) {
		return -1;
	}
	struct node* prev_tail = list->tail;
	prev_tail->next = new_node;
	list->tail = new_node;	
}


int insert_after_node_single_linked_list(struct linked_list* list, struct node* node, void* value){
	if (node == NULL){
		fprintf(stderr, "ERROR: Node uninitialized\n");
		return -1;
	}
	if(node->next == NULL && list->tail != node) {
		return -1;
	}
	if (node->next == NULL && list->tail == node) {
		//fprintf(stderr, "ERROR: Do not use this to update the list tail");
		return insert_tail_single_linked_list(list,value);
	}
	
	struct node* new_node;
	new_node = make_single_linked_node(value);
	if (new_node == NULL) {
		return -1;
	}
	new_node->data = value;
	new_node->next = node->next;
	node->next = new_node;
	return 0;
}

int take_step_single_linked_list(struct node* node, int step_size){
	if (node == NULL){
		return -1;
	}
	int i;
	for (i = 0; i<step_size; i++){
		if(node) {
			node = node->next;
		}
		else {
			break;
		}
	}
	if (i == step_size && node != NULL) {
		return 0;
	}
	return -1;
}

struct node* goto_index_single_linked_list(struct linked_list* list, int index) {
	if (list == NULL || list->head == NULL) {
		return (struct node*) NULL;
	}
	struct node* node = list->head;
	if(take_step_single_linked_list(node, index) == -1){
		return (struct node*) NULL;
	}
	return node;
}
int insert_index(struct linked_list* list, void* value, int index){
 	if (list == NULL || list->head == NULL) {
		return -1;
	}
	struct node* node = goto_index_single_linked_list(list, index);
	if(node == NULL){
		return -1;
	}
	return insert_after_node_single_linked_list(list, node, value);
}



void print_int_single_linked_list(struct linked_list* list){
	if (list == NULL || list->head == NULL) {
		fprintf(stderr, "ERROR: Uninitialized or empty list\n");
		return;
	}
	printf("LIST HEAD -> ");
	struct node* node = list->head;
	int* ptr;
	while(node) {
		if(node->data){
			ptr = (int*) node->data;
			printf("%d",*ptr);
		}
		if(node->next){
			printf(" -> ");
		}
		node = node->next;
	}
	printf("\n");
} 	 			


int main(int argc, char** argv) {
	struct linked_list* list = init_single_linked_list();
	int first = 7;
	int second = 4;
	insert_head_single_linked_list(list, (void*) &first);
	insert_tail_single_linked_list(list, (void*) &second);
	insert_head_single_linked_list(list, (void*) &second);
	print_int_single_linked_list(list);
}

