/* Code to implement mergesort on a singly linked list 
 * Complexity: O(n log n) for n nodes 
 * Uses divide and conquer methodology 
 * Sorts in place (no new allocations of nodes 
 */

#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/* Linked list node struct - I'm not going to use head here but 
 * its an easy generalization 
 */

struct node {
	int value;
	struct node* next; 
};

/* Method to create a node 
 * O(1) assuming memory allocation is constant time 
 */

struct node* init_node(int val) {
	struct node* node = (struct node*) malloc(sizeof(struct node));
	if (node == NULL) {
		return NULL;
	}
	node->value = val; 
	node->next = NULL;
	return node; 
}

/* Method to insert a node at the head of a list
 * before the existing node 
 * Returns a pointer to the new node 
 */

struct node* insert_front(struct node* old, int val) {
	struct node* new_root = init_node(val);
	if(new_root == NULL) {
		return NULL;
	}
	new_root->next = old;
	return new_root;
}

/* Method to find median node in a linked list that 
 * nerminates with a node pointing to NULL
 * Does so by counting the number of nodes, and then going halfway
 * You can also use two pointers, 1 going by 2s, one going normally 
 * This has time complexity O(n) 
 */

struct node* get_median(struct node* root) {
        if (root == NULL || root->next == NULL) {
		return root;
	}	
	int count = 0;
	struct node* curr = root; 
	while(curr) {
		curr = curr->next;
		count++;
	}
	//Get median by dividing the count by two
	curr = root;
	count = count/2;
	int i = 0;
	for (i = 0; i<count; i++) {
		curr = curr->next;
	}
	return curr; 
}

/* Merge merges two distinct single linked lists 
 * demarcated by pointers, start1 end1, start2, end2
 * end pointers denote the location pointing to the final node in the list 
 * Takes O(n) time 
 * Returns pointer to head of the list, or NULL
 */

struct node* merge(struct node* start_a, struct node* start_b) {
	if (start_a == NULL || start_b == NULL) {
	//Error - uninitializzed lists 
		return NULL;
	}
	//set the start of the list to be the start node with the smaller value 
	struct node* root;
	struct node* curr;
	struct node* prev;
	struct node* start;
	struct node* temp;
	struct node* comp;
	if (start_a->value > start_b->value) {
		root = start_b;
		start = start_a;
		comp = start_a;
	}
	else {
		root = start_a;
		start = start_b;
		comp = start_b; 
	}

	curr = root->next;
	prev = root;
	while(comp  && curr) {
		if (comp->value < curr->value) {
			temp = comp->next;
			comp->next = curr;
			prev->next = comp;
			prev = comp;
			comp = temp; 
		}
		else {
			//advance curr
			temp = curr;
			curr = curr->next;
			prev = curr; 
		}
	}
	if (comp == NULL && curr) {
	//	curr-> next= NULL;
		return root;
	}
	//attach remaining nodes to the end of list
	prev->next = comp;
	return root; 

}

struct node* mergesort_sll(struct node* start, struct node* end) {
	if (start == NULL ) {
		return NULL;
	}
	if (start == end || start->next == NULL) {
		return start;
	}
	if (end && start->next == end) {
		if (end->value < start->value){
			int temp = start->value;
			start->value = end->value;
			end->value = temp;
		}
		end->next = NULL;
		return start;
	}
	struct node* median = get_median(start);
	if(median == NULL || median->next == NULL) {
		return NULL;
	}
	struct node* after_median = median->next;
	struct node* a = mergesort_sll(start, median);
	struct node* b = mergesort_sll(after_median, end);
	return merge(a,b);
}  	 
