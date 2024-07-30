#ifndef BIN_TREE_H__
#define BIN_TREE_H__

#include <stdio.h>

#include "item.h"

typedef struct type_tree
{
    item_t *item;
    struct type_tree *left;
    struct type_tree *right;
} tree_t;

tree_t *tree_create(item_t *item);

void tree_free(tree_t *pt);

void tree_destroy(tree_t *pt);

void tree_print(FILE *f, tree_t *pt);

void tree_print_dot(FILE *f, tree_t *pt);

tree_t *tree_find(tree_t *pt, tree_t *el, int (*comp)(item_t *, item_t *));

tree_t *tree_insert(tree_t *pt, tree_t *el, int (*comp)(item_t *, item_t *));

#endif