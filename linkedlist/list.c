/*-
 * Copyright (c) 2013 Abhinav Upadhyay <er.abhinav.upadhyay@gmail.com>
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in
 *    the documentation and/or other materials provided with the
 *    distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * ``AS IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE
 * COPYRIGHT HOLDERS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY OR CONSEQUENTIAL DAMAGES (INCLUDING,
 * BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
 * AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
 * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT
 * OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
 * SUCH DAMAGE.
 */

#include <assert.h>
#include <stdio.h>
#include <stdlib.h>

typedef struct list {
    void *data;
    struct list *next;
} list;


list *
list_init(void)
{
    list *l = NULL;
    return l;
}

void
list_add(list **head, void *data)
{
    list *node = malloc(sizeof(list));
    node->data = data;
    node->next = *head;
    *head = node;
}

void
list_remove(list **head, list *node)
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

void list_merge(list **h1, list **h2)
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
    list *l = list_init();
    int i;
    for (i = 0; i < len; i++)
        list_add(&l, &a[i]);
    return l;
}

static void
list_print(list *l)
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
    list_print(l1);
    printf("l2:\n");
    list_print(l2);
    list_merge(&l1, &l2);
    printf("merged list:\n");
    list_print(l1);
    return 0;
}




