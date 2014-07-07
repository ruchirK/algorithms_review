#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/* Code that, when given a 2D array of zeroes and ones, checks for the 
 * 'islands of 0s' or groups of adjacent 0s. 0s must be horizontally 
 * or vertically directly next to each other in order to be adjacent
 * Diagonals don't count here 
 * Algorithm - parses array going first left-right, then top down
 * Each element checks above and to its left to see if there are any neighboring 
 * elements with a value > 1. Otherwise, if it is 0, and there is a neighbor like that
 * its value gets copied over, otherwise it gets overwritten by current # of sets seen + 2
 * Note that while this overwrites the array, it doen't actually destroy it 
 * Since checking each element takes constant time + constant time overwrites 
 * on a n by n array it takes O(n^2) and computes the result with no extra space 
 */ 

char check_point (char** array, int x, int y, int m, int n) {
    if (x < 0 || x >= m || y < 0 || y >= n) {
        return (char) -1;
    } //invalid point 

    if (array[x][y] >= '0') {
        return array[x][y] - '0';
    }
    return array[x][y];
}

int check_neighbors(char* array[],int* set_num ,  int x, int y, int m, int n) {
    char val = check_point(array, x, y, m, n);
    if (val < 0) {
        return -1; //invalid
    }
    if (val == 1) {
        return 0;
    }
    //now we need to check the neighbors
    char left = check_point(array, x - 1, y, m, n);
    char top = check_point(array, x, y - 1, m, n);
    if (left > 1 ){
       array[x][y] = left;
       return 0;
   }
   if (top > 1) {
        array[x][y] = top;
        return 0;
    }
    array[x][y] = (char) (*set_num)++;
    return 0;

}
int main (int argc, char** argv) {
    char buf[20];
    int m = 0;
    int n = 0;
    fgets(buf, 20, stdin);
    printf("%s\n", buf);
    m = strlen(buf) - 1;
    int sets = 2;
    int i = 0;
    n = m;
    char** array = (char**) calloc( n , sizeof(char*));
    char* array_row;
    while(strlen(buf) - 1 == m){
        array_row = (char*) calloc(m,  sizeof(char));
        strncpy(array_row, buf, n);
        array[i++] = array_row;
        fgets(buf, 20, stdin);
   }
   int j = 0;
    for(i =0; i< n; i++) {
        for(j =0; j<n; j++) {
            check_neighbors(array, &sets, j, i,  n, n);
        }
    } 
    printf("Number of disjoint blobs of zeroes %d\n", sets-2); 
   
}
