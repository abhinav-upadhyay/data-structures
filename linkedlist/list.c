#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct list {
    void *data;
    struct list *next;
} list;


list *
init(void)
{
    list *l = NULL;
    return l;
}

void
insert(list **head, void *data)
{
    list *node = malloc(sizeof(list));
    node->data = data;
    node->next = *head;
    *head = node;
}

void
delete(list **head, list *node)
{
    list *prevnode;
    list *curnode;
    if (*head == node) {
        *head = (*head)->next;
        return;
    }

    prevnode = *head;
    curnode = (*head)->next;
    while(curnode) {
        if (curnode == node) {
            prevnode->next = curnode->next;
            free(curnode);
            return;
        }
        prevnode = curnode;
        curnode = curnode->next;
    }
}

void merge(list **h1, list **h2)
{
    list *l3 = NULL;
    list *l1 = *h1;
    list *l2 = *h2;
    list *h3;
    while (l1 && l2) {
        if (*(int *)l1->data <= *(int *)l2->data) {
            if (l3 == NULL) {
                l3 = l1;
                h3 = l1;
            }
            else {
                l3->next = l1;
                l3 = l3->next;
            }
            l1 = l1->next;
        } else {
            if (l3 == NULL) {
                l3 = l2;
                h3 = l3;
            }
            else {
                l3->next = l2;
                l3 = l3->next;
            }
            l2 = l2->next;
        }
    }

    while (l1) {
        l3->next = l1;
        l1 = l1->next;
        l3 = l3->next;
    }

    while (l2) {
        l3->next = l2;
        l2 = l2->next;
        l3 = l3->next;
    }
    *h1 = h3;
    return;
}


static list *
getlist(int *a, size_t len)
{
    list *l = init();
    int i;
    for (i = 0; i < len; i++)
        insert(&l, &a[i]);
    return l;
}

static void
print(list *l)
{
    list *l1 = l;
    while(l1 != NULL) {
        printf("%d\n", *(int *)l1->data);
        l1 = l1->next;
    }
}

int
main(int argc, char **argv)
{
    int a1[] = {8, 6, 4};
    list *l1 = getlist(a1, 3);
    int a2[] = {12, 10, 5, 3};
    list *l2 = getlist(a2, 4);
    printf("l1:\n");
    print(l1);
    printf("l2:\n");
    print(l2);
    merge(&l1, &l2);
    printf("merged list:\n");
    print(l1);
    return 0;
}




