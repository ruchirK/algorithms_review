#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int* binary_search(int* arr, int len, int to_search) {
	//Performs binary search on integer array arr 
	//returns pointer to the integer being searched for 

	//check if list is null or empty 
	if (arr == NULL || len == 0) {
		return NULL; 
	}
	if (len == 1) {
		if ((*arr) == to_search) {
			return arr;
		}
		else {
			return NULL; 
		}
	}
	int* mid_point = arr + len/2;
	if ((*mid_point) == to_search) {
		return mid_point;
	}
	if ((*mid_point) > to_search) {
		return binary_search(arr, len/2, to_search);
	}
	else {
		return binary_search(mid_point, len - len/2, to_search);
	}
}

int main(int argc, char** argv) {
	int sorted[10] = {1, 3, 7, 11, 13, 29, 31, 35, 46, 51 };
	int* result = binary_search(sorted, 10, 28);
	printf("What is my result %d", *result);

} 
