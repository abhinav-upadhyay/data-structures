#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
#include "list.h"

static void
print_callback(void *p)
{
    printf("%d\n", *(int *) p);
}

int
main(int argc, char **argv)
{
    int a1[] = {8, 6, 4};
    list *l1 = getlist(a1, 3);
    printf("l1:\n");
    list_print(l1, print_callback);
    list_free(l1, NULL);
    return 0;
}
