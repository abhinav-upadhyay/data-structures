#include <stdio.h>
#include <stdlib.h>
#include "hashtable.h"

int
main(int argc, char **argv)
{
    hashtable *ht = init(10);
    const char *x = "abhinav";
    put(ht, "name", (void *) x);
    printf("%s\n", get(ht, "name"));
    clear(ht);
    return 0;
           
}
