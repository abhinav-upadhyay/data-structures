#ifndef HASH_H
#define HASH_H
typedef struct {
    void **q;
    size_t size;
} hashtable;

hashtable *init(size_t);
void put(hashtable *, char *, void *);
char *get(hashtable *, char *);
#endif
