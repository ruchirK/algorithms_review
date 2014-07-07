#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Code to reverse a string in place   
//This assumes base 10 conversion, but can be generalized to any base
//Currently converts first continuous substring of valid characters into an int 
//Ignores decimal points, signs and everything else
int my_atoi(char* input ) {
	if (input == NULL) {
		return -1;
	}
	int i;
	int value = 0;
	int power = 1;
	for(i = 0; i< strlen(input); i++){
		if (input[i] >= '0' && input[i] <= '9'){
			value = power * value  + (input[i] - '0');
			power = 10;
		}
		else if (power > 1) {
			break;
		}
	}
	if (power > 1) { return value; }
	return -1;
}
int main(int argc, char** argv) {
	//Remember that char* and char[] are two different initializations and
	//the first is immutable
	char string_one[] = "he6438ffffe4567";
	printf("Originals: %s %s\n", string_one, string_two);
	int number = my_atoi(string_one);	
	printf("Converted number: %s %d\n", string_one, number);

	return 0;

}
	
