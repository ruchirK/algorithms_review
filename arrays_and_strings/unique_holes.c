#include <stdio.h>
#include <stdlib.h>
#include <string.h>


char check_point (char** array, int x, int y, int m, int n) {
    if (x < 0 || x >= m || y < 0 || y >= n) {
        return (char) -1;
    } //invalid point 

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
    //char right = check_point(array, x + 1, y, m, n);
    char top = check_point(array, x, y + 1, m, n);
    //char bottom = check_point(array, x, y - 1, m, n);
    if (left > 1 ){
       array[x][y] = left;
       return 0;
   }
   if (top > 1) {
        array[x][y] = top;
        return 0;
    }
    array[x][y] = (char) *set_num++;
    return 0;

}

    
