#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Code to reverse a string in place   

void reverse(char* input) {
	char* front = input;	//pointer to front of string
	char* end = input + strlen(input) -1;	//pointer to end of string
	char temp;
	while (front < end){
		//fprintf(stderr, "DEBUG: In While loop %s %c\n", input, *end);
		temp = *front;		//Set front to a temporary
		*front = *end;		//Set the character at front inde equal to end
		*end = temp;		//Set character at end index equal to front
		front++;		//Advance front_index (move right)
		end--;			//Decrement end index (move left)
	}
}

//Test driver 

int main(int argc, char** argv) {
	//Remember that char* and char[] are two different initializations and
	//the first is immutable
	char string_one[] = "helo";
	char string_two[] = "goodbye";
	printf("Originals: %s %s\n", string_one, string_two);
	reverse(string_one);	
	reverse(string_two);
	printf("Reversed: %s %s\n", string_one, string_two);

	return 0;

}
	
