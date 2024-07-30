#ifndef AVL_TREE_H__
#define AVL_TREE_H__

#include <stdio.h>

#include "item.h"

typedef struct type_avl
{
    item_t *item;
    int depth;
    struct type_avl *left;
    struct type_avl *right;
} avl_t;

avl_t *avl_create(item_t *item);

void avl_free(avl_t *pt);

void avl_destroy(avl_t *pt);

void avl_print(FILE *f, avl_t *pt);

void avl_print_dot(FILE *f, avl_t *pt);

avl_t *avl_find(avl_t *pt, avl_t *el, int (*comp)(item_t *, item_t *));

avl_t *avl_insert(avl_t *pt, avl_t *el, int (*comp)(item_t *, item_t *));

#endif