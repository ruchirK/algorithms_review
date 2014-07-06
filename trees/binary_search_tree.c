/* Implementation of binary search trees and standard dictionary functions:
 * insert, search, delete - all of which run in O(h) time
 * find-min and find-max - also O(h)
 * and standard traversals, which run in O(n) for n nodes 
 */
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


struct b_node { 
	int value; //not doing generics because most applications use ints 
	struct b_node* parent;
	struct b_node* left;
	struct b_node* right;
};


/* Creates a node storing a value, and sets parent, and left right child 
 * equal to null
 */ 

struct b_node* init_node(int data) {
	struct b_node* node = calloc(1, sizeof(struct b_node));
	//Check for invalid allocation
	if (node == NULL) {
		return node; //
	} 
	node->value = data;
	return node;
}
/* Recursively insets an integer into correct place 
 * in binary search tree 
 * O(h) best case O(log n) worst case O(n) for n nodes
 * Returns a pointer to the inserted node
 */
struct b_node* insert_bst(struct b_node* node,struct b_node* parent,  int data) {
	//If both node and parent are null then this is a brand new tree
	if(node == NULL) {
		struct b_node* new_node = init_node(data);
		if (new_node == NULL) {
			return new_node;
		}
		new_node->parent = parent;
		return new_node;
	}
	if(node->value > data) {
	//This leess than current node value, so it must be a left child/descendant
		return insert_bst(node->left, node, data);
	}
	if(node->value < data){
	//This is greater than value of current node - must be right child/descendant
		return insert_bst(node->right, node, data);
	}
	//Clearly, data must now be equal to node->value so this depends on how 
	//you define insertions of duplicates, I'm going to just make it return 
	//the existing pointer
	return node;

}

/* Wrapper over insert_bst that allows it to be called without specifying parent
 * everything else is the same
 */


struct b_node* insert(struct b_node* root, int data) {
	if (root == NULL) {
		return insert_bst(root, NULL, data);
	}
	return insert_bst(root, root->parent, data);
}

/* Search method - essentialy performs binary search on the bst structure
 * Takes O(h) same best and worse case performance as above
 * Returns pointer to node containing the int being searched
 * or NULL on error 
 */ 

struct b_node* search_bst(struct b_node* node, int data) {
	if (node == NULL) {
	//Nonexisting node - return NULL
		return NULL;
	}
	if (node-> value == data) {
	//Found the correct value
		return node;
	}
	if (node->value > data) {
	//Data being searched is too small, has to be in 
	//left subtree 
		return search_bst(node-> left, data);
	}

	if(node->value < data) {
	//Data is too big has to be in ln
	//right subtree 
		return search_bst(node->right, data);
	}

	//We have covered all three comparison cases, so reaching 
	//here is only possible with error
	return NULL;
}
/* Swap - helper function for delete_node_bst() 
 * Swaps the contents of two nodes - their parents and the 
 * references in their parent pointers 
 * The second argument can be NULL - used if a leaf node is 
 * being deleted, but the first has to be non NULL
 * Returns 0 on success, -1 on error
 * O(1) runtime 
 */

int swap_nodes (struct b_node* a, struct b_node* b) {
	if (a == NULL) {
	//Invalid input 
		return -1;
	}
	if (a->parent) {
	//Assign a's parent the pointer to b
	//Since you can't actually swap values 
		if(a->parent->left == a) {
		//a was left child of its parent, thats b now
			a->parent->left = b;
		}
		else if(a->parent->right == a) {
		//a was right child of its parent 
			a->parent->right = b;
		}
		else {
		//This is an invalid BST where a's parent doesn't contain a 
		//pointer to a - this is an error
			return -1;
		}
	}
	if (b == NULL) {
	//There's no actual swapping to be done, we just changed a's parent's pointer
	//for safety's sake let's change a->parent as well, but this node should
	//most likely be deleted 
		a->parent = NULL;
		return 0;
	}

	//If we are here, b exists, and so we need
	//to swap parent pointers
	//and change parent references

	if(b->parent) {
	//Assign b's parent the pointer to a 
		if(b->parent->left == b) {
		//a was left child of its parent, thats b now
			b->parent->left = a;
		}
		else if(b->parent->right == b) {
		//a was right child of its parent 
			b->parent->right = a;
		}
		else {
		//This is an invalid BST where a's parent doesn't contain a 
		//pointer to a - this is an error
			return -1;
		}
	}
	//Now we have to swap the pointers in the nodes themselves 
	struct b_node* temp = a->parent;
	a->parent = b->parent;
	b->parent = temp;
}	
/* Deletes a node from a binary search tree 
 * Three cases to consider - node has 0,i 1, or two kids 
 * First two are trivial and can be done in constant time 
 * Third one requires that you replace the node being deleted
 * with its in order successor 
 * which is (in this case) just the minimum (leftmost node) in right subtree 
 * Time complexity O(h) in worst case - same as above
 * Returns 0 on success, and -1 on error
 */
int delete_node_bst(struct b_node* to_delete) {
	if(to_delete == NULL) {
	//Nonexisting node - this really depends on the semantics of 'error'
	//Some could argue that the job was already done here, and this is a success
	//But no nodes were actually deleted, and this is an invalid input
		return -1;
	}
	if(to_delete->left == NULL && to_delete->right == NULL) {
	//This is a leaf node - can be deleted really easily 
	//First clear reference in parent 
		if(swap_nodes(to_delete, NULL) < 0) {
		//Error occured while swapping
			return -1; 
		}
		free(to_delete);
		return 0;
	}

	//Now we need to consider the two separate cases where the node
	//has only 1 child 
	if(to_delete->left && to_delete->right == NULL) {
	//only has left child
		if(swap_nodes(to_delete, to_delete->left) < 0) {
			return -1;
		}
		free(to_delete);
		return 0;
	}

	if(to_delete->right && to_delete->left == NULL) {
	//only has right child
		if(swap_nodes(to_delete, to_delete->right) < 0) {
			return -1;
		}
		free(to_delete);
		return 0;
	}
 	//Has ro have two kids, so we get the successor, swap those nodes, then
	//delete that node 
	//we know the successor can't have two kids - otherwise its 
	//left child would be smaller 
	struct b_node* successor = find_min(to_delete->right);
	if(swap_nodes(to_delete, successor) < 0) {
		return -1;
	}
	return delete_node_bst(to_delete);
	//The successor node now occupies to_deletes original
	//position in the tree 

}
