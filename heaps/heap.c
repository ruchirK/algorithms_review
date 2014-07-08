/* Code that implements binary heap data structure 
 * for min or max heaps 
 * Supported operations:
 * get-min or get max O(1)
 * insert             O(log n)
 * delete             O(log n)
 * heapify 
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


struct heap {
	int* array;
	int capacity;
	int curr_size;

};
 
/* init_heap initializes a empty heap with capacity 
 * equal to max_size 
 * heap is filled with zeroes
 * returns pointer to heap or NULL on error 
 * O(1) complexity
 */ 
struct heap* init_heap(int max_size) {
	struct heap* heap = (struct heap*) malloc(sizeof(struct heap));
	if(heap == NULL) {
		return NULL;
	}
	heap->capacity = max_size;
	heap->curr_size = 0;
	heap->array = (int *)  calloc(max_size,sizeof(int));
	if(heap->array == NULL) {
		free(heap);
		return NULL;
	}
	return heap; 

} 
 
