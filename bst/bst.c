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

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include "bst.h"

static node *
get_new_node(node *parent, int key, void *value)
{
    node *newnode = malloc(sizeof(node));
    if (!newnode)
        return NULL;
    newnode->key = key;
    newnode->value = value;
    newnode->left = NULL;
    newnode->right = NULL;
    newnode->parent = parent;
    return newnode;
}

node *
init(int key, void *value)
{
    return get_new_node(NULL, key, value);
}
    
bool
insert(node *root, int key, void *value)
{
    if (key >= root->key) {
        if (root->right == NULL) {
            root->right = get_new_node(root, key, value);
            return root->right? true: false;
        } else
            return insert(root->right, key, value);
    } else {
        if (root->left == NULL) {
            root->left = get_new_node(root, key, value);
            return root->left? true: false;
        } else
            return insert(root->left, key, value);
    }
}

    
static node *
_search(node *root, int key)
{
    if (root->key == key)
        return root;
    if (root->key > key)
        if (root->left)
            return _search(root->left, key);
        else
            return NULL;
    if (root->key <= key)
        if (root->right)
            return _search(root->right, key);
        else
            return NULL;
}

void *
search(node *root, int key)
{
    node *result = _search(root, key);
    if (result)
        return result->value;
    else
        return NULL;
}

static node *
_get_max(node *root)
{
    if (root->right == NULL)
        return root;
    else return _get_max(root->right);
}

bool
delete(node *root, int key)
{
    node *n = _search(root, key);
    int left;
    int right;
    if (n->parent == NULL) {
        left = 0;
        right = 0;
    }
    else if (n == n->parent->left)
        left = 1;
    else
        right = 1;

    if (n == NULL)
        return false;

    /* If the node to be deleted is a leaf node */
    if (!n->left && !n->right) {
        if (left) {
            n->parent->left = NULL;
        } else if (right) {
            n->parent->right = NULL;
        }
        free(n);
        return true;
    }

    /* If the node has only one child */
    if (n->left == NULL) {
        if (left) {
            n->parent->left = n->right;
        } else if (right) {
            n->parent->right = n->right;
        }
        free(n);
        return true;
    } else if (n->right == NULL) {
        if (left) {
            n->parent->left = n->right;
        } else if (right) {
            n->parent->right = n->right;
        }
        free(n);
        return true;
    }

    /* If the node has two children
     * We replace the node, with the one in its left subtree having the maximum key.
     */
    node *maxnode = _get_max(n->left);
    n->key = maxnode->key;
    n->value = maxnode->value;
    return delete(maxnode, maxnode->key);
}

void
inorder_print(node *root)
{
    if (root == NULL)
        return;

    if (root->left)
        inorder_print(root->left);
    printf("%d\n", root->key);
    if (root->right)
        inorder_print(root->right);
}

void
bst_free(node *root, void (*free_callback)(void *))
{
    if (root == NULL)
        return;
    node *left = root->left;
    node *right = root->right;
    if (free_callback)
        free_callback(root->value);
    free(root);
    bst_free(left, free_callback);
    bst_free(right, free_callback);
}
            


