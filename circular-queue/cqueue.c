#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "cqueue.h"

cqueue *
cqueue_init(size_t size)
{
   cqueue *cq = malloc(sizeof(cqueue));
   if (cq == NULL)
       return NULL;

   cq->max_size = size;
   cq->tail= 0;
   cq->head = -1;
   cq->data = malloc(sizeof(void *) * size);
   if (cq->data == NULL) {
       free(cq);
       return NULL;
   }
   memset(cq->data, 0, cq->max_size);
   return cq;
}

void
cqueue_append(cqueue *cq, void *d)
{
    cq->data[cq->tail] = d;
    if (cq->head == -1)
        cq->head = 0;
    cq->tail = (cq->tail + 1) % cq->max_size;
}

void
cqueue_pop(cqueue *cq)
{
    if (cq->head == -1)
        return;
    cq->head = (cq->head + 1) % cq->max_size;
    if (cq->head > cq->tail) {
        cq->head = -1;
        cq->tail = 0;
    }
}

void
cqueue_remove(cqueue *cq, size_t n)
{
    int i;
    for (i = 0; i < n; i++) {
        cqueue_pop(cq);
        if (cq->head == -1)
            return;
    }
}

void
cqueue_list(cqueue *cq, void (*print_callback)(void *d))
{
    int i;
    if (cq->head == -1)
        return;

    for (i = cq->head; i < cq->tail; i++)
        print_callback(cq->data[i]);
}

void
cqueue_free(cqueue *cq, void (*free_callback)(void *))
{
    int i;
    if (cq->head == -1)
        return;
    for (i = 0; i < cq->max_size; i++)
        free_callback(cq->data[i]);
    free(cq->data);
    free(cq);
}



