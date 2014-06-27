#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Code to determine whether two strings are permutations of each other  
//One relatively easy method is to use a 'prime number hash' 
//made by mapping each letter to a prime, and multiplying the hash
//by that prime every time you encounter that number
//and then compare the hashes of the two strings

//Program to generate an upper bounded approximation of a log
int approximate_log(int n){
	int log = 1;
	while(n > 0) {
		n = n >> 1;
		log++;
	}
	return ++log;
}

//Lets include some code to generate the array of primes

int* generate_primes(int n) {
	//generates the first n primes (2 is indeed as zeroeth, technically is first)
	int* prime_array = (int*) calloc(n, sizeof(int));
	int gen_len = n * approximate_log(n);
	int* generating_array = (int*) calloc(gen_len, sizeof(int));
	//use sieve of erasthones to generate primes
	int i,j;
	for (i = 2; i< gen_len; i++){
		if (!generating_array[i]) {
			//Hasn't been declared not prime yet so must be prime
			generating_array[i] = 1;
			 j = i * i;
			 while(j<gen_len) {
				generating_array[j] = -1; //Set as not a prime
				j += i;
			 }
		}
	}
	//Now copy the declared primes onto the prime number array
	i = 0;
	j = 0;
	for (i = 0; i <n; i++) {
		while(j < gen_len && generating_array[++j] !=1){
			//Wait till j advances to the next prime number
			;
		}
		//Copy that number onto the prime array
		prime_array[i] = j;
	}
	free(generating_array);
	return prime_array;
}

//Now the actual string comparison code
//Again this takes only lowercase alphabetic ccharacters but
//can be generalized to any finite alphabet

long compute_hash(char* string, int* primes) {
	long hash = 1;
	int value = 0;
	int i;
	for (i = 0; i<strlen(string); i++) {
		value = string[i] - 'a';
		if(value < 0 || value > 25){
			fprintf(stderr, "DEBUG: Invalid character in string %s \n", string);
			return -1;
		}
		else {
			hash *= primes[value];
		}
	}
	return hash;
}

int permutation(char* string_one, char* string_two, int* primes){

	long hash_one = compute_hash(string_one, primes);
	long hash_two = compute_hash(string_two, primes);
	if (hash_one < 0 || hash_two < 0) {
		fprintf(stderr, "DEBUG ERROR: One or more of these strings was invalid %s %s \n", string_one, string_two);
		return -1;
	}
	
	else {
		if (hash_one == hash_two) {
			return 0;
		}
		return 1;
	}
}

//Test driver 

int main(int argc, char** argv) {
	int n = 26;
	int i;
	int* primes = generate_primes(n);

	for(i = 0; i<n; i++) {
		printf("%d %d \n", i, primes[i]);
	}

	char* one = "damp";
	char* two = "pramd";
	int result = permutation(one, two, primes);
	printf("%s %s %d\n", one, two, result);
	return 0;
}

