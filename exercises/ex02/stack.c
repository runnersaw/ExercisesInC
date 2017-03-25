/* Example code for Think OS.

Copyright 2014 Allen Downey
License: GNU GPLv3

*/

#include <stdio.h>
#include <stdlib.h>

#define SIZE 5

int *foo() {
    int i;
    int array[SIZE];

    //printf("%p\n", array);

    // Set every element in the array to 42
    for (i=0; i<SIZE; i++) {
        array[i] = 42;
    }

    // RETURNS A POINTER TO STACK-ALLOCATED DATA THAT WILL BE REMOVED
    // AS SOON AS THE FUNCTION RETURNS
    return array;
}

void bar() {
    int i;
    int array[SIZE];

    //printf("%p\n", array);

    // Set elements in this array to 0,1,2,3,4
    for (i=0; i<SIZE; i++) {
	   array[i] = i;
    }
}

int main()
{
    int i;
    // Gets a pointer to an array that has been deallocated
    int *array = foo();

    // Bar may or may not modify the memory allocated by foo()
    bar();

    // Print out array -- probably will be garbage!
    for (i=0; i<SIZE; i++) {
	   printf("%d\n", array[i]);
    }

    return 0;
}
