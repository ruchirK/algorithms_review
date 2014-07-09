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

struct hash_node {
	int value;
	struct hash_node* next; 
};

struct hashtable { 
	int size;
	struct hash_node** array; 
	int num_elements;
}; 





