#include <stdlib.h>
#include <string.h>

#include "tree_node.h"

tree_t *tree_create(char *filename, char *access, char *owner, char *size, int year, int month, int day, int hour, int minute)
{
    tree_t *new_el = NULL;
    new_el = malloc(sizeof(tree_t));
    if (new_el)
    {
        new_el->filename = filename;
        new_el->access = access;
        new_el->owner = owner;
        new_el->size = size;
        new_el->year = year;
        new_el->month = month;
        new_el->day = day;
        new_el->hour = hour;
        new_el->minutes = minute;

        new_el->left = NULL;
        new_el->right = NULL;
    }

    return new_el;
}

void tree_free(tree_t *pt)
{
    if (pt->filename)
        free(pt->filename);
    if (pt->access)
        free(pt->access);
    if (pt->owner)
        free(pt->owner);
    if (pt->size)
        free(pt->size);
    free(pt);
}

int cmp_filename(tree_t *pl, tree_t *pr)
{
    return strcmp(pl->filename, pr->filename);
}

int cmp_date(tree_t *pl, tree_t *pr)
{
    if (pl->year != pr->year)
        return (pl->year - pr->year);
    if (pl->month != pr->month)
        return (pl->month - pr->month);
    if (pl->day != pr->day)
        return (pl->day - pr->day);   
    if (pl->hour != pr->hour)
        return (pl->hour - pr->hour);
    if (pl->minutes != pr->minutes)
        return (pl->minutes - pr->minutes);

    return 0;
}