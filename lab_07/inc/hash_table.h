#ifndef HASH_TABLE_H__
#define HASH_TABLE_H__

#include "item.h"

#define N          50

typedef struct type_list
{
    item_t *item;
    struct type_list *next;
} list_t;

typedef struct type_hash
{
    int size;
    int count;
    list_t **overflow;
    item_t **items;
} hash_t;

list_t *allocate_list(void);

list_t *list_insert(list_t *list, item_t *item);

void list_free(list_t *list);

list_t **create_overflow(hash_t *table);

void free_overflow(hash_t *table);

int hash_func(char *str);

hash_t *hash_create(int size);

void hash_free(hash_t *table);

void hash_collision(hash_t *table, int index, item_t *item);

void hash_collision2(hash_t *table, int index, item_t *item);

int hash_insert(hash_t *table, item_t *item);

char *hash_find(hash_t *table, char *word);

char *hash_find2(hash_t *table, char *word);

void hash_print(FILE *f, hash_t *table);

#endif