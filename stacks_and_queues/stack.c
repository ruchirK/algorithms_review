#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct stack {
	int max_size;
	int curr_head;
	int* array; 
};

struct stack* init_stack(int size) {

	if (size <= 0) {
		return NULL;
	}
	struct stack* my_stack = (struct stack*) malloc(sizeof(struct stack));
	if (my_stack == NULL) {
		return my_stack;
	}

	my_stack->max_size = size;
	my_stack->curr_head = 0;
	my_stack->array = (int*) calloc(size, sizeof(int));
	if(my_stack->array == NULL) {
		free(my_stack);
		return NULL;
	}
	return my_stack;
 
}

int push (struct stack* stack, int to_insert) {
	if (stack == NULL || stack->max_size == stack->curr_head) {
		//fixed size stack - can easily double capacity here if we want
		//choosing to do it this way though
		return -1;
	}

	if (stack->array[stack->curr_head] != 0 ) {
		return -1; 
		//This means you can't insert zero 
	}

	stack->array[stack->curr_head] = to_insert;
	(stack->curr_head)++;
	return 0;

}

int pop(struct stack* stack) {
	if (stack == NULL || stack->curr_head == 0 || stack->max_size == 0) {
		return -1;
	}
	return stack->array[stack->curr_head--]; 
}

void delete_stack(struct stack* stack) {
	if (stack == NULL || stack->max_size == 0 || stack->array == NULL) {
		return;
	}
	free(stack->array);
	free(stack);
}
