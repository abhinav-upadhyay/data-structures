#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

int
main(int argc, char **argv)
{
    const char *v1 = "name";
    const char *v2 = "age";
    const char *v3 = "school";
    const char *v4 = "college";
    const char *v5 = "address";

    node *tree = init(25, (void *)v1);
    insert(tree, 12, (void *)v2);
    insert(tree, 10, (void *) v3);
    insert(tree, 35, (void *) v4);
    insert(tree, 45, (void *) v5);
    inorder_print(tree);
    bst_free(tree, NULL);
    return 0;
}
    
