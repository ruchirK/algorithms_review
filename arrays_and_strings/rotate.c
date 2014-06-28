#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//reverses char * at the specified indicies 

int partial_reverse(char* start, char* end) {
	if (start == 0 || end == 0){
		fprintf(stderr, "ERROR: One or more of the pointers is NULL\n");
		return -1;
	}
	if (start > end) {
		fprintf(stderr, "ERROR: The inputs seem to be out of order\n");
		return -1;
	}

	if (*end == '\0'){
		fprintf(stderr, "ERROR: End pointer points to NULL character\n");
		return -1;
	}
	char temp;
	while (start < end) {
		temp = *start;
		*start = *end;
		*end = temp;
		start++;
		end--;
	}
	return 0;
}

int reverse(char* input){
	return partial_reverse(input, input + strlen(input)-1);
}

int rotate(char* input, int amount) {
	//if amount is positive, right rotate, otherwise lefr rotate
	if(input == 0){
		//invalid pointer
		return -1;
	}
	int len = strlen(input);
	if (len == 0) {
		return 0;
	}
	amount = amount % len;
	if (amount == 0){
		return 0;
	}
	if ( amount < 0 ) {
		amount = len + amount;
	}
	if(reverse(input) < 0) {
		return -1;
	}
	partial_reverse(input, input + amount - 1);
	partial_reverse(input + amount, input + len -1);

	return 0;

}
		
		
		
		


//Test driver 

int main(int argc, char** argv) {
	//Remember that char* and char[] are two different initializations and
	//the first is immutable
	char string_one[] = "helo";
	char string_two[] = "goodbye";
	printf("Originals: %s %s\n", string_one, string_two);
	rotate(string_one, 2);
	rotate(string_two, -4);
	printf("Modified: %s %s \n", string_one, string_two);

	return 0;
}
	
