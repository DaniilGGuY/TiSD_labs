#include <string.h>
#include <stdlib.h>

#include "hash_table.h"
#include "err_codes.h"

list_t *allocate_list(void) 
{
    list_t *list = malloc(sizeof(list_t));
    return list;
}

list_t *list_insert(list_t *list, item_t *item) 
{
    list_t *head = allocate_list();
    head->item = item;
    head->next = NULL;
    if (!list)
        return head;

    list_t *temp = list;
    while (temp->next)
        temp = temp->next;
  
    temp->next = head;
  
    return list;
}

void list_free(list_t *list) 
{
    list_t *tmp = list;
    while (list) 
    {
        tmp = list;
        list = list->next;
        item_free(tmp->item);
        free(tmp);
    }
}

list_t **create_overflow(hash_t *table) 
{
    list_t **buck = calloc(table->size, sizeof(list_t *));
    for (int i = 0; i < table->size; ++i)
        buck[i] = NULL;

    return buck;
}

void free_overflow(hash_t *table) 
{
    list_t **buck = table->overflow;
    for (int i = 0; i < table->size; ++i)
          list_free(buck[i]);
    free(buck);
}

int hash_func(char *str)
{
    int index = 0;
    for (size_t i = 0; i < strlen(str); ++i)
        index += (str[i] - 'a');

    return index % N;
}

hash_t *hash_create(int size)
{
    hash_t *table = malloc(sizeof(hash_t));
    table->size = size;
    table->count = 0;
    table->items = calloc(table->size, sizeof(hash_t *));
    for (int i = 0; i < table->size; ++i)
        table->items[i] = NULL;

    table->overflow = create_overflow(table);

    return table;
}

void hash_free(hash_t *table)
{
    for (int i = 0; i < table->size; ++i) 
    {
        item_t *item = table->items[i];
        if (item)
            item_free(item);
    }

    free_overflow(table);
    free(table->items);
    free(table);
}

void hash_collision(hash_t *table, int index, item_t *item) 
{
    list_t *head = table->overflow[index];

    if (!head) 
    {
        head = allocate_list();
        head->item = item;
        table->overflow[index] = head;
    }
    else 
        table->overflow[index] = list_insert(head, item);
 }

void hash_collision2(hash_t *table, int index, item_t *item)
{
    while (table->items[index % table->size])
        ++index;

    table->items[index] = item;
}

int hash_insert(hash_t *table, item_t *item)
{
    int ind = hash_func(item->word);
    item_t *found_item = table->items[ind];
    if (!found_item) 
    {
        if (table->count == table->size)
        {
            item_free(item);
            return ERR_FULL;
        }
    
        table->items[ind] = item;
        ++table->count;
    }
    else
    {
        if (item_cmp(found_item, item) != 0)
            hash_collision2(table, ind, item);
        else
            item_free(item);
    }

    return OK;
}

char *hash_find(hash_t *table, char *word) 
{
    int index = hash_func(word);
    item_t *item = table->items[index];
    list_t *head = table->overflow[index];
    while (item)
    {
        if (strcmp(item->word, word) == 0)
            return item->description;
        if (!head)
            return NULL;

        item = head->item;
        head = head->next;
    }

    return NULL;
}

char *hash_find2(hash_t *table, char *word) 
{
    int index = hash_func(word);
    for (int i = 0; i < table->size && strcmp(table->items[index]->word, word); ++i, index = (index + 1) % table->size)
        ++index;

    if (strcmp(table->items[index]->word, word) != 0)
        return NULL;

    return table->items[index]->description;
}

void hash_print(FILE *f, hash_t *table)
{
    for (int i = 0; i < table->size; ++i)
        if (table->items[i])
        {
            fprintf(f, "Index: %d, Key: %s\nValue: %s\n", i, table->items[i]->word, table->items[i]->description);
            if (table->overflow[i]) 
            {
                list_t *head = table->overflow[i];
                while (head) 
                {
                    fprintf(f, "Index: %d, Key: %s\nValue: %s\n", i, head->item->word, head->item->description);
                    head = head->next;
                }
            }
        }
}