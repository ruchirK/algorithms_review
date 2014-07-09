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
	heap->array = (int *)  calloc(max_size + 1,sizeof(int));
	if(heap->array == NULL) {
		free(heap);
		return NULL;
	}
	return heap; 

} 

/* Get min / get max returns a copy of the min/max of the heap 
 * and doesn't remove it from the heap 
 * O(1) compleexity 
 * Returns integer or zero on error 
 */ 

int get_min(struct heap* heap) {
	if(heap == NULL || heap->capacity == 0 ||  heap->array == NULL || heap->curr_size == 0 ) {
		return 0;
	}
	return heap->array[(curr_size)];
}

int get_max(struct heap* heap) {
	if(heap == NULL || heap->capacity == 0 ||  heap->array == NULL || heap->curr_size == 0 ) {
		return 0;
	}
	return heap->array[(curr_size)];
}

/* insert__min and insert_max place an element into the bottom of the heap and then 
 * 'bubbles' it up if it is less/greater than its parent node 
 * Complexity O(n) 
 */ 

int insert_min_heap(struct heap* heap, int data) {
	if (heap == NULL || heap->array == NULL || heap->capacity == NULL || heap->curr_size == heap->capacity) {
		return -1; 
	}
	heap->array[heap->curr_size + 1] = data; 
	int parent = 0;
	if (heap->curr_size > 0){
		parent = (heap->curr_size)/2; 
	}
	int curr = heap->
	
