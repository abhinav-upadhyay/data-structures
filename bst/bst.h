#ifndef _BST_H
#define _BST_H
typedef struct node {
    int key;
    void *value;
    struct node *left;
    struct node *right;
    struct node *parent;
    int rank;
} node;

bool insert(node *, int, void *);
bool delete(node *, int);
void *search(node *, int);
node *init(int, void *);
void inorder_print(node *);
void bst_free(node *root, void (*free_callback) (void *));

#endif


