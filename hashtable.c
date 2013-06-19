# include <math.h>
# include <stdio.h>
# include <stdlib.h>
#include <string.h>
# include "hashtable.h"

static int
hash(char *str, int size)
{
    int i;
    int hashcode = 0;
    size_t len = strlen(str);
    const unsigned int c = (int) pow(255, len);
    for (i = 0; i < len; i++) {
        hashcode += (c / pow(255, i + 1)) * str[i];
    }
    return hashcode % size;
}

hashtable *
init(size_t size)
{
    hashtable *ht;
    if ((ht = malloc(sizeof(hashtable))) == NULL)
        return NULL;
    ht->q = calloc(size, sizeof(void *));
    if (ht->q == NULL) {
        free(ht);
        return NULL;
    }
    ht->size = size;
    memset(ht->q, 0, size);
    return ht;
}

void
put(hashtable *ht, char *key, void *value)
{
    int index = hash(key, 10);
    ht->q[index] = value;
}

char *
get(hashtable *ht, char *key)
{
    int index = hash(key, 10);
    return ht->q[index];
}

void
clear(hashtable *ht)
{
    int i;
    for (i = 0; i < ht->size; i++)
        free(ht->q[i]);
    free(ht);
}

