#ifndef TREE_H__
#define TREE_H__

#include <stdio.h>

#include "tree_node.h"

void tree_destroy(tree_t *pt);

void tree_print(FILE *f, tree_t *pt);

void tree_print_dot(FILE *f, tree_t *pt, const char *name);

void pre_order(tree_t *pt);

void in_order(tree_t *pt);

void post_order(tree_t *pt);

tree_t *tree_find(tree_t *pt, tree_t *el, int (*comp)(tree_t *, tree_t *));

tree_t *tree_insert(tree_t *pt, tree_t *el, int (*comp)(tree_t *, tree_t *));

tree_t *tree_delete(tree_t *pt, tree_t *el, int (*comp)(tree_t *, tree_t *));

tree_t *tree_delete_task(tree_t *pt, tree_t *el, int (*comp)(tree_t *, tree_t *));

tree_t *tree_delete_task_sorted(tree_t *pt, tree_t *el, int (*comp)(tree_t *, tree_t *));

#endif