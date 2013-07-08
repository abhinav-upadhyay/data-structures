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
#include <string.h>
# include "hashtable.h"

static int
hash(char *str, int size)
{
    int i;
    int hashcode = 0;
    size_t len = strlen(str);
    const unsigned int c = (int) pow(ALPHABET_SIZE, len);
    for (i = 0; i < len; i++) {
        hashcode += (c / pow(ALPHABET_SIZE, i + 1)) * str[i];
    }
    return hashcode % size;
}

hashtable *
init(size_t size)
{
    hashtable *ht;
    if ((ht = malloc(sizeof(hashtable))) == NULL)
        return NULL;
    ht->q = (void **) calloc(size, sizeof(void *));
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

void *
get(hashtable *ht, char *key)
{
    int index = hash(key, 10);
    return ht->q[index];
}

void
clear(hashtable *ht)
{
    free(ht->q);
    free(ht);
}

