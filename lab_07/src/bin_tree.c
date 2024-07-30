#include <stdlib.h>

#include "bin_tree.h"

tree_t *tree_create(item_t *item)
{
    tree_t *tree = malloc(sizeof(tree_t));
    if (tree)
    {
        tree->item = item;
        tree->left = NULL;
        tree->right = NULL;
    }

    return tree;
}

void tree_free(tree_t *pt)
{
    item_free(pt->item);
    free(pt);
}

void tree_destroy(tree_t *pt)
{
    if (!pt)
        return;

    tree_destroy(pt->left);
    tree_destroy(pt->right);

    tree_free(pt);
}

void tree_print(FILE *f, tree_t *pt)
{
    if  (!pt)
        return;
        
    if (pt->left)
        fprintf(f, "%s -> %s;\n", pt->item->word, pt->left->item->word);

    if (pt->right)
        fprintf(f, "%s -> %s;\n", pt->item->word, pt->right->item->word);
        
    tree_print(f, pt->left);
    tree_print(f, pt->right);
}

void tree_print_dot(FILE *f, tree_t *pt)
{
    fprintf(f, "digraph outgraph {\n");
    tree_print(f, pt);
    fprintf(f, "}\n");
}

tree_t *tree_find(tree_t *pt, tree_t *el, int (*comp)(item_t *, item_t *))
{
    int cmp;
    if (pt == NULL)
        return NULL;

    cmp = comp(el->item, pt->item);
    if (cmp == 0)
        return pt;
    else if (cmp < 0)
        return tree_find(pt->left, el, comp);
    else
        return tree_find(pt->right, el, comp);
}

tree_t *tree_insert(tree_t *pt, tree_t *el, int (*comp)(item_t *, item_t *))
{
    int cmp;

    if (pt == NULL)
        return el;

    cmp = comp(el->item, pt->item);
    if (cmp < 0)
        pt->left = tree_insert(pt->left, el, comp);
    else if (cmp > 0)
        pt->right = tree_insert(pt->right, el, comp);

    return pt;
}
