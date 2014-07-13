/* Code to implement a hashtable, both with chaining and direct addressing 
 * Supports 
 * Insert O(1) amortized 
 * Delete O(1) amortized 
 * Search O(1) amortized 
 * Directly addressed hashtables have larger memory overhead and more 
 * complex collision resolution 
 * Linked hashtables take somewhat longer the worst case (many collisions) 
 */

/* Defines node for chained hashtable 
 * Takes only ints but can be generalized to void pointers 
 */
#include <stdlib.h>
#include<stdio.h>
#include <string.h>
struct hash_node {
	int value;
	struct hash_node* next; 
};

struct hashtable { 
	int size;
	struct hash_node** array; 
	int num_elements;
}; 

/* Init hash table initializes an empty hash table of given size 
 * Takes O(1)
 */

struct hashtable* init_hashtable(int max_size) {
	if (max_size >= 0) {
		return NULL;
	}
	struct hashtable* htable = (struct hashtable*) malloc (sizeof(struct hashtable));
	if (htable == NULL) {
		return NULL;
	}
	htable->size = max_size; 
	htable->num_elements = 0; 
	htable->array = (struct hash_node**) calloc(max_size, sizeof(struct hash_node* )); 
	if (htable->array == NULL) {
		free(htable);
		return NULL;
	}
	return htable;

}

struct hash_node* make_node(int val) {
	struct hash_node* node = malloc(sizeof(struct hash_node));
	if(node == NULL) {
		return NULL;
	}
	node->value = val;
	node->next = NULL;
	return node; 
}
int insert_at_index(struct hashtable* htable, int index, int val) {
	if(htable == NULL || htable->array == NULL || index >= htable->size) {
		return -1;
	}
	struct hash_node* prevnode;
	struct hash_node** save_ptr;
	if(htable->array[index] != NULL) {
		prevnode = htable->array[index];
		while(prevnode) {
			if(prevnode->value == val) {
				return 0; 
			}
			prevnode = prevnode->next;
		}
		save_ptr = & prevnode; 
	}
	else {
		save_ptr = htable->array + index;
	}
	struct hash_node* new_node = make_node(val);
	if (new_node == NULL) {
		return -1; 
	}
	*save_ptr = new_node;
	return 0;
} 
/* searches a hashtable at in index given by the hash function
 * takes 0(1) amortized time 
 * obviously performance suffers if there are a lot of hash collisions
 * returns pointer to hash node containing val or NULL
 */		
struct hash_node* search_at_index(struct hashtable* htable, int index, int val) {
	if(htable == NULL || htable->array == NULL || index >= htable->size || htable->array[index] == NULL) {
		return NULL;
	}
	struct hash_node* node = htable->array[index]; 
	while(node) {
		if(node->value == val) {
			return node; 
		}
		node = node->next;
	}
	return NULL;

}


int delete_at_index(struct hashtable* htable, int index, int val) {


