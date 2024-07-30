#include <stdlib.h>

#include "avl_tree.h"

avl_t *avl_create(item_t *item)
{
    avl_t *tree = malloc(sizeof(avl_t));
    if (tree)
    {
        tree->item = item;
        tree->depth = 1;
        tree->left = NULL;
        tree->right = NULL;
    }

    return tree;
}

void avl_free(avl_t *pt)
{
    item_free(pt->item);
    free(pt);
}

void avl_destroy(avl_t *pt)
{
    if (!pt)
        return;

    avl_destroy(pt->left);
    avl_destroy(pt->right);

    avl_free(pt);
}

void avl_print(FILE *f, avl_t *pt)
{
    if  (!pt)
        return;
        
    if (pt->left)
        fprintf(f, "%s -> %s;\n", pt->item->word, pt->left->item->word);

    if (pt->right)
        fprintf(f, "%s -> %s;\n", pt->item->word, pt->right->item->word);
        
    avl_print(f, pt->left);
    avl_print(f, pt->right);
}

void avl_print_dot(FILE *f, avl_t *pt)
{
    fprintf(f, "digraph outgraph {\n");
    avl_print(f, pt);
    fprintf(f, "}\n");
}

avl_t *avl_find(avl_t *pt, avl_t *el, int (*comp)(item_t *, item_t *))
{
    int cmp;
    if (pt == NULL)
        return NULL;

    cmp = comp(el->item, pt->item);
    if (cmp == 0)
        return pt;
    else if (cmp < 0)
        return avl_find(pt->left, el, comp);
    else
        return avl_find(pt->right, el, comp);
}

static int height(avl_t *pt) 
{
    return pt ? pt->depth : 0;
}

static int delta_height(avl_t *pt) 
{
    return height(pt->right) - height(pt->left);
}

static void fix_height(avl_t *pt) 
{
    int hl = height(pt->left);
    int hr = height(pt->right);
    pt->depth = (hl > hr ? hl : hr) + 1;
}

static avl_t *right_rotate(avl_t *pt) 
{
    avl_t *qt = pt->left;
    pt->left = qt->right;
    qt->right = pt;
    fix_height(pt);
    fix_height(qt);

    return qt;
}

static avl_t *left_rotate(avl_t *pt) 
{
    avl_t *qt = pt->right;
    pt->right = qt->left;
    qt->left = pt;
    fix_height(pt);
    fix_height(qt);

    return qt;
}

static avl_t *balance(avl_t *pt) 
{
    fix_height(pt);

    if (delta_height(pt) == 2) {
        if (delta_height(pt->right) < 0)
            pt->right = right_rotate(pt->right);
        return left_rotate(pt);
    }

    if (delta_height(pt) == -2) {
        if (delta_height(pt->left) > 0)
            pt->left = left_rotate(pt->left);
        return right_rotate(pt);
    }

    return pt;
}

avl_t *avl_insert(avl_t *pt, avl_t *el, int (*comp)(item_t *, item_t *))
{
    int cmp;

    if (pt == NULL)
        return el;

    cmp = comp(el->item, pt->item);
    if (cmp < 0)
        pt->left = avl_insert(pt->left, el, comp);
    else if (cmp > 0)
        pt->right = avl_insert(pt->right, el, comp);

    return balance(pt);
}
