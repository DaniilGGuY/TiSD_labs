#define _GNU_SOURCE

#include <stdlib.h>
#include <string.h>

#include "item.h"
#include "err_codes.h"

item_t *item_create(void)
{
    item_t *item = malloc(sizeof(item_t));
    if (item)
    {
        item->word = NULL;
        item->description = NULL;
    }

    return item;
}

int item_input(FILE *f, item_t *item)
{
    ssize_t read;
    size_t len = 0;
    int rc = OK;
    char *buf_w = NULL, *buf_d = NULL;
    if (f == stdin)
        printf("Input word:\n");
    if ((read = getline(&buf_w, &len, f)) == -1)
        rc = ERR_MEM;
    if (read <= 1 && !rc)
        rc = ERR_IO;
    if (!rc && buf_w[read - 1] == '\n')
        buf_w[read - 1] = '\0';

    if (!rc && f == stdin)
        printf("Input description:\n");
    if (!rc && (read = getline(&buf_d, &len, f)) == -1)
        rc = ERR_MEM;
    if (read <= 1 && !rc)
        rc = ERR_IO;
    if (!rc && buf_d[read - 1] == '\n')
        buf_d[read - 1] = '\0';

    if (!rc)
    {
        item->word = buf_w;
        item->description = buf_d;
    }
    else
    {
        if (buf_w)
            free(buf_w);
        if (buf_d)
            free(buf_d);
    }

    return rc;
}

void item_free(item_t *item)
{
    if (item->word)
        free(item->word);
    if (item->description)
        free(item->description);
    free(item);
}

int item_cmp(item_t *pl, item_t *pr)
{
    return strcmp(pl->word, pr->word);
}
