/* Example code for Exercises in C.

Copyright 2014 Allen Downey
License: Creative Commons Attribution-ShareAlike 3.0

*/

#include <stdio.h>
#include <stdlib.h>
#include <assert.h>


void free_anything(int *p) {
    free(p);
}


int read_element(int *array, int index) {
    int x = array[index];
    return x;
}


int main ()
{
    int *allocated = malloc(sizeof(int));
    int *free_once = malloc (sizeof (int));
    int *use_before_free = malloc (sizeof (int));
    int *definitely_freed = malloc (sizeof (int));
    int array1[100];
    int *array2 = malloc (100 * sizeof (int));

    // valgrind does not bounds-check static arrays
    read_element(array1, 0);
    read_element(array1, 99);

    // but it does bounds-check dynamic arrays
    read_element(array2, 0);
    read_element(array2, 99);

    // and it catches use after free
    *use_before_free = 17;
    free(use_before_free);
    
    // never_free is definitely lost
    *definitely_freed = 17;
    free(definitely_freed);

    // the following line would generate a warning
    free(array2);

    // but this one doesn't
    free_anything(allocated);
    
    free(free_once);

    return 0;
}
