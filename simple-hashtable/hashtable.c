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

# include <math.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include "hashtable.h"
# include "list.h"

static int
hash(const char *str, int size)
{
    int i;
    int hashcode = 0;
    size_t len = strlen(str);
    const unsigned int c = (int) pow(SH_ALPHABET_SIZE, len);
    for (i = 0; i < len; i++) {
        hashcode += (c / pow(SH_ALPHABET_SIZE, i + 1)) * str[i];
    }
    return hashcode % size;
}

hashtable *
init(size_t max_size)
{
    hashtable *ht;
    size_t init_size = max_size <= 0? SH_DEFAULT_TABLE_SIZE: max_size;
    
    if ((ht = malloc(sizeof(hashtable))) == NULL)
        return NULL;
    ht->buckets = calloc(init_size, sizeof(list *));
    if (ht->buckets == NULL) {
        free(ht);
        return NULL;
    }
    ht->max_size = max_size;
    ht->size = 0;
    memset(ht->buckets, 0, init_size);
    return ht;
}

static void
resize(hashtable **ht)
{
    int i;
    size_t newsize = (*ht)->max_size * 2;

    hashtable *new_ht = init(newsize);
    if (new_ht == NULL)
        return;

    for (i = 0; i < (*ht)->max_size; i++) {
        list *l = (*ht)->buckets[i];
        while (l) {
            /*
             *TODO What happens if while copying the linked list the new
             * hashtable goes out of space and resize is called again?
             */
            put(&new_ht, ((pair *)l->data)->key, ((pair *)l->data)->value);
            l = l->next;
        }
    }
    clear(*ht);
    *ht = new_ht;
}

int
put(hashtable **table, const char *key, void *value)
{
    hashtable *ht = *table;
    pair *p = malloc(sizeof(pair));
    if (p == NULL)
        return -1;

    size_t keylen = strlen(key) + 1;
    p->key = malloc(keylen);
    if (p->key == NULL) {
        free(p);
        return -1;
    }
    memcpy((void *)p->key, (void *)key, keylen);
    p->value = value;
    int index = hash(key, ht->max_size);
    if (ht->buckets[index] == NULL) {
        ht->buckets[index] = list_init();
        ht->size++;
    }
    list_add(&ht->buckets[index], p);
    if (ht->size == ht->max_size)
        resize(table);
    return 0;
}

void *
get(hashtable *ht, const char *key)
{
    int index = hash(key, ht->max_size);
    list *l = ht->buckets[index];
    while (l) {
        if (strncmp(((pair *)l->data)->key, key, strlen(key)) == 0)
            return ((pair *)l->data)->value;
        l = l->next;
    }
    return NULL;
}

static void
free_pair(void *d)
{
    pair *p = (pair *) d;
    free((void *)p->key);
    free(p);
}

void
clear(hashtable *ht)
{
    int i;
    for (i = 0; i < ht->size; i++)
        list_free(ht->buckets[i], free_pair);
    free(ht->buckets);
    free(ht);
}

