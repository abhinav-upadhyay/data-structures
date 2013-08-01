#ifndef CQUEUE_H
#define CQUEUE_H

typedef struct {
    size_t max_size;
    int tail;
    int head;
    void **data;
} cqueue;

cqueue *cqueue_init(size_t);
void cqueue_append(cqueue *, void *);
void cqueue_remove(cqueue *, size_t);
void cqueue_pop(cqueue *);
void cqueue_list(cqueue *, void (*print_callback)(void *));
void cqueue_free(cqueue*, void (*free_callback)(void *));
#endif
