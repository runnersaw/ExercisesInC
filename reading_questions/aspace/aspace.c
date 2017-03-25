/* Example code for Think OS.

Copyright 2014 Allen Downey
License: GNU GPLv3

*/

#include <stdio.h>
#include <stdlib.h>

int global;

int main ()
{
    int t = 5;
    int local = 5;
    int l = 5;
    void *p = malloc(24);
    void *q = malloc(24);

    printf ("Address of main is %p\n", main);
    printf ("Address of global is %p\n", &global);
    printf ("Address of t is %p\n", &t);
    printf ("Address of local is %p\n", &local);
    printf ("Address of l is %p\n", &l);
    printf ("Address of p is %p\n", p);
    printf ("Address of q is %p\n", q);

    return 0;
}
