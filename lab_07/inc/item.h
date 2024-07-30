#ifndef ITEM_H__
#define ITEM_H__

#include <stdio.h>

typedef struct type_item
{
    char *word;
    char *description;
} item_t;

item_t *item_create(void);

int item_input(FILE *f, item_t *item);

void item_free(item_t *item);

int item_cmp(item_t *pl, item_t *pr);

#endif