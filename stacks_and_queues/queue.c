#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct queue {
	int max_size;
	int curr_front;
	int curr_back;
	int* array; 
};

struct queue* init_queue(int size) {

	if (size <= 0) {
		return NULL;
	}
	struct queue* my_queue = (struct queue*) malloc(sizeof(struct queue));
	if (my_queue == NULL) {
		return my_queue;
	}

	my_queue->max_size = size;
	my_queue->curr_front = 0;
	my_queue->curr_back = 0;
	my_queue->array = (int*) calloc(size, sizeof(int));
	if(my_queue->array == NULL) {
		free(my_queue);
		return NULL;
	}
	return my_queue;
 
}

int enqueue (struct queue* queue, int to_insert) {
	if (queue == NULL || queue->max_size == queue->curr_front) {
		//fixed size stack - can easily double capacity here if we want
		//choosing to do it this way though
		return -1;
	}

	if (queue->array[queue->curr_front] != 0 ) {
		return -1; 
		//This means you can't insert zero 
	}

	queue->array[queue->curr_front] = to_insert;
	queue->curr_front = (queue->curr_front + 1)  % queue->max_size;
	return 0;

}

int dequeue(struct queue* queue) {
	if (queue == NULL || queue->max_size == 0) {
		return -1;
	}
	int to_return = queue->array[queue->curr_back];
	queue->array[queue->curr_back] = 0;
	queue->curr_back = (queue->curr_back + 1) % queue->max_size;

	return to_return;
}

void delete_queue(struct queue* queue) {
	if (queue == NULL || queue->array == NULL) {
		return;
	}
	free(queue->array);
	free(queue);
}
