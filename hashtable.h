#ifndef HASH_H
#define HASH_H
typedef struct {
    void **q;
    size_t size;
} hashtable;

hashtable *init(size_t);
void put(hashtable *, char *, void *);
void *get(hashtable *, char *);
void clear(hashtable *);
#endif
