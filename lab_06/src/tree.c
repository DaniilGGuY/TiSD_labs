#include "err_codes.h"
#include "tree.h"

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
        fprintf(f, "%s -> %s;\n", pt->filename, pt->left->filename);

    if (pt->right)
        fprintf(f, "%s -> %s;\n", pt->filename, pt->right->filename);
        
    tree_print(f, pt->left);
    tree_print(f, pt->right);
}

void tree_print_dot(FILE *f, tree_t *pt, const char *name)
{
    fprintf(f, "digraph %s {\n", name);
    tree_print(f, pt);
    fprintf(f, "}\n");
}

void pre_order(tree_t *pt)
{
    if (!pt)
        return;

    printf("%s\n", pt->filename);
    pre_order(pt->left);
    pre_order(pt->right);
}

void in_order(tree_t *pt)
{
    if (!pt)
        return;

    in_order(pt->left);
    printf("%s\n", pt->filename);
    in_order(pt->right);
}

void post_order(tree_t *pt)
{
    if (!pt)
        return;

    post_order(pt->left);
    post_order(pt->right);
    printf("%s\n", pt->filename);
}

tree_t *tree_find(tree_t *pt, tree_t *el, int (*comp)(tree_t *, tree_t *))
{
    int cmp;
    if (pt == NULL)
        return NULL;

    cmp = comp(el, pt);
    if (cmp == 0)
        return pt;
    else if (cmp < 0)
        return tree_find(pt->left, el, comp);
    else
        return tree_find(pt->right, el, comp);
}

tree_t *tree_insert(tree_t *pt, tree_t *el, int (*comp)(tree_t *, tree_t *))
{
    int cmp;

    if (pt == NULL)
        return el;

    cmp = comp(el, pt);
    if (cmp < 0)
        pt->left = tree_insert(pt->left, el, comp);
    else
        pt->right = tree_insert(pt->right, el, comp);

    return pt;
}

static tree_t *del_el_tree(tree_t *pt)
{
    if (!pt)
        return NULL;
    if (!pt->left && !pt->right)
    {
        tree_free(pt);
        pt = NULL;
    }
    else if (!pt->left && pt->right)
    {
        tree_t *old_el = pt;
        pt = pt->right;
        tree_free(old_el);
    }
    else if (pt->left && !pt->right)
    {
        tree_t *old_el = pt;
        pt = pt->left;
        tree_free(old_el);
    }
    else
    {
        tree_t *old_el = pt, *last_el;
        pt = pt->left;
        if (pt->right)
        {
            while (pt->right)
                pt = pt->right;
            pt->left = old_el->left;
            pt->right = old_el->right;
            last_el = old_el->left;
            while (last_el->right != pt)
                last_el = last_el->right;
            last_el->right = NULL;
        }
        else
            pt->right = old_el->right;   

        tree_free(old_el);    
    }

    return pt;
}

tree_t *tree_delete(tree_t *pt, tree_t *el, int (*comp)(tree_t *, tree_t *))
{
    int cmp;

    if (pt == NULL)
        return NULL;

    cmp = comp(el, pt);
    if (cmp < 0)
        pt->left = tree_delete(pt->left, el, comp);
    else if (cmp > 0)
        pt->right = tree_delete(pt->right, el, comp);
    else
        pt = del_el_tree(pt);

    return pt;
}

tree_t *tree_delete_task(tree_t *pt, tree_t *el, int (*comp)(tree_t *, tree_t *))
{
    int cmp;

    if (pt == NULL)
        return NULL;

    cmp = comp(el, pt);
    if (cmp > 0)
    {
        pt = del_el_tree(pt);
        pt = tree_delete_task(pt, el, comp);
    }
    else
    {
        pt->left = tree_delete_task(pt->left, el, comp);
        pt->right = tree_delete_task(pt->right, el, comp);
    }

    return pt;
}

tree_t *tree_delete_task_sorted(tree_t *pt, tree_t *el, int (*comp)(tree_t *, tree_t *))
{
    int cmp;

    if (pt == NULL)
        return NULL;

    cmp = comp(el, pt);
    if (cmp == 0)
        tree_destroy(pt->left);
    else if (cmp < 0)
        pt->left = tree_delete_task_sorted(pt->left, el, comp);
    else
    {
        tree_destroy(pt->left);
        pt = tree_delete_task_sorted(pt->right, el, comp);
        pt = del_el_tree(pt);
    }

    return pt;
}