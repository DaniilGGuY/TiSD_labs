#include <string.h>

#include "item.h"
#include "err_codes.h"
#include "process.h"

int read_avl(FILE *f, avl_t **avl)
{
    item_t *el = NULL;
    avl_t *el_avl = NULL;
    int rc = OK;
    while (!feof(f) && !rc)
    {
        el = item_create();
        if (!el)
            rc = ERR_MEM;
        if (!rc)
            rc = item_input(f, el);
        if (!rc)
            el_avl = avl_create(el);

        if (el_avl)
        {
            *avl = avl_insert(*avl, el_avl, item_cmp);
            el_avl = NULL;
        }
        else
            rc = ERR_MEM;
    }

    return rc;
}

int read_tree(FILE *f, tree_t **tree)
{
    item_t *el = NULL;
    tree_t *el_tree = NULL;
    int rc = OK;
    while (!feof(f) && !rc)
    {
        el = item_create();
        if (!el)
            rc = ERR_MEM;
        if (!rc)
            rc = item_input(f, el);
        if (!rc)
            el_tree = tree_create(el);

        if (el_tree)
        {
            *tree = tree_insert(*tree, el_tree, item_cmp);
            el_tree = NULL;
        }
        else
            rc = ERR_MEM;
    }

    return rc;
}

int read_hash(FILE *f, hash_t **tree)
{
    item_t *el = NULL;
    hash_t *el_hash = hash_create(N);
    int rc = OK;
    if (!el_hash)
        return ERR_MEM;
    
    while (!feof(f) && !rc)
    {
        el = item_create();
        if (!el)
            rc = ERR_MEM;
        if (!rc)
            rc = item_input(f, el);
        if (!rc)
            rc = hash_insert(el_hash, el);
    }

    if (!rc)
        *tree = el_hash;
    else
        if (el_hash)
            hash_free(el_hash);

    return rc;
}

int read_str(char **buf)
{
    ssize_t read; 
    size_t len = 0;
    int rc = OK;
    char *tmp = NULL;

    if ((read = getline(&tmp, &len, stdin)) == -1)
        rc = ERR_MEM;
    if (read <= 1 && !rc)
        rc = ERR_IO;
    if (!rc && tmp[read - 1] == '\n')
        tmp[read - 1] = '\0';

    *buf = tmp;

    return rc;
}