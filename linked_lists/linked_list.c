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

int delete_head_single_linked_list(struct linked_list* list, void** result_ptr) {
	if (list == NULL){
		fprintf(stderr, "ERROR: Linked list uninitialized\n");
		return -1;
	}
	if (list->head == NULL){
		fprintf(stderr, "ERROR: Linked list empty\n");
		return -1;
	}
	struct node* new_head = list->head->next;
	struct node* old = list->head;
	if (result_ptr) {
		*result_ptr = list->head->data;
	}
	if(list->head == list->tail){
		list->tail = new_head;
	}
	list->head = new_head;
	free(old);
	return 0;
}

int delete_single_linked_list(struct linked_list* list, void** result_ptr) {
	if (list == NULL){
		fprintf(stderr, "ERROR: Linked list uninitialized\n");
		return -1;
	}
	if (list->head == NULL){
		fprintf(stderr, "ERROR: Linked list empty\n");
		return -1;
	}
	struct node* new_head = list->head->next;
	while(list->head){
		delete_head_single_linked_list(list, NULL);
	}
	free(list);

	return 0;
}
	

int get_prev(struct linked_list* list, struct node* to_find, struct node** result_node) {
	if (list == NULL){
		fprintf(stderr, "ERROR: Linked list uninitialized\n");
		return -1;
	}
	if (list->head  == NULL){
		fprintf(stderr, "ERROR: Linked list empty\n");
		return -1;
	}
	if (result_node == NULL) {
		fprintf(stderr, "ERROR: Pointer to store result in is uninitialized\n");
		return -1;
	}
	if(to_find == NULL) {
		fprintf(stderr, "ERROR: Please enter a valid node to search for\n");
		return -1;
	}
	if (to_find == list->head){
		*result_node = (struct node *) NULL;
		return 0;
	}
	struct node* node = list->head;
	while (node){
		if(to_find == node->next) {
			*result_node = node;
			return 0;
		}
		node = node->next;
	}
	return -1;
}  

int delete_tail_single_linked_list(struct linked_list* list, void** result_ptr) {
	if (list == NULL){
		fprintf(stderr, "ERROR: Linked list uninitialized\n");
		*result_ptr = NULL;
		return -1;
	}
	if (list->tail == NULL){
		fprintf(stderr, "ERROR: Linked list empty\n");
		*result_ptr = NULL;
		return -1;
	}
	struct node* new_tail;
	struct node* old = list->tail;
	if (get_prev(list, list->tail, &new_tail) < 0) {
		return -1;
	}
	if (result_ptr) {
		*result_ptr = list->tail->data;
	}
	if(list->head == list->tail){
		list->head = new_tail;
	}
	new_tail->next = NULL;
	list->tail = new_tail;
	free(old);
	return 0;
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

int delete_node_single_linked_list(struct linked_list* list, struct node* node, void** result_ptr){
	if (node == NULL){
		fprintf(stderr, "ERROR: Node uninitialized\n");
		return -1;
	}
	if(node->next == NULL && list->tail != node) {
		return -1;
	}
	if (node == list->head){
		return delete_head_single_linked_list(list, result_ptr);
	}
	if (node->next == NULL && list->tail == node) {
		//fprintf(stderr, "ERROR: Do not use this to update the list tail");
		return delete_tail_single_linked_list(list, result_ptr);
	}
	struct node* temp = node->next;
	if(result_ptr) {
		*result_ptr = node->data;
	}
	node->data = node->next->data;
	node->next = node->next->next;
	free(temp);
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
int reverse_single_linked_list(struct linked_list* list) {
	if (!list || !(list->head) ) {
		return -1;
	}
	struct node* curr = list->head;
	struct node* next;
	struct node* prev = NULL; 
	while(curr) {
		next = curr->next; 
		curr->next = prev;
		prev = curr;
		curr = next;
	}

	if (!list->head || !list->tail || !list->tail->next) {
		return -1;
	}
	//swap head and tail
	curr = list->head;
	list->head = list->tail;
	list->tail = curr;
	return 0;
}	

int main(int argc, char** argv) {
	struct linked_list* list = init_single_linked_list();
	int first = 7;
	int second = 4;
	insert_head_single_linked_list(list, (void*) &first);
	insert_tail_single_linked_list(list, (void*) &second);
	insert_head_single_linked_list(list, (void*) &first);
	print_int_single_linked_list(list);
//	delete_tail_single_linked_list(list, (void**) NULL);
	reverse_single_linked_list(list);
	print_int_single_linked_list(list);
	delete_single_linked_list(list, NULL);

	return 0;

}
