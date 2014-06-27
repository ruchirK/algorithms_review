#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Code to determine whether a string is composed  of all unique characters 

//First implementation does so with a true bitvector 
//Assumes that input string contains only lowercase ascii encoded letters
//Takes O(n) where n is size of input string 
//If there are no other data structures allowed, then it takes O(n^2) to look ahead in string for each letter 
int all_unique_bitvector(char* input) {
	unsigned int bitvector = 0;
	int i; 	//index
	int char_value;
	for (i = 0; i < strlen(input) ; i++) {
		//get the numerical value of the letter from 0 - 25 for a to z 
		char_value = input[i] - 'a'; 
		//NOTE: to generalize, change the above logic
		//Check if integer is within correct rangle
		if (char_value < 0 || char_value > 25) {
			fprintf(stderr, "DEBUG: Invalid integer returned %d \n", char_value);
			return -1;
		}
		//Now check that bit in the bitvector has already been set
		//Do this using left bitshifting and bitwise AND
		//Letter 'a' is LSB, 'z' is 25th bit
		if ((bitvector & (1 << char_value)) == 0) {
			//Set that bit high
			//For this use bitwise OR
			bitvector = bitvector | (1 << char_value); 
		}
		//Otherwise, the bit has already been set
		//So that letter has already been seen
		else {
			return -1;
		}
	}
	//Now it has seen all the letters and still not returned 
	//So all letters must be unique 
	return 0;
}

//Test driver 

int main(int argc, char** argv) {
	char* string_one = "helo";
	char* string_two = "goodbye";
	int result_one = all_unique_bitvector(string_one);
	int result_two = all_unique_bitvector(string_two);

	printf("%s result %d; %s result %d \n", string_one, result_one, string_two, result_two);
	return 0;

}
	
