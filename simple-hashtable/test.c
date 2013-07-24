#include <stdio.h>
#include <stdlib.h>
#include "hashtable.h"

int
main(int argc, char **argv)
{
    hashtable *ht = init(1);
    const char *x = "abhinav";
    int age = 22;
    const char *y = "abcd";
    put(ht, "name", (void *) x);
    put(ht, "age", (void *) &age); 
    put(ht, "random", (void *) y);
    printf("%s\n", (char *) get(ht, "name"));
    printf("%d\n", *(int *)get(ht, "age"));
    printf("%s\n", (char *) get(ht, "random"));
    clear(ht);
    return 0;
           
}
