#ifndef TREE_NODE_H__
#define TREE_NODE_H__

typedef struct tree_type
{
    char *filename;
    char *access;
    char *owner;
    char *size;
    int year;
    int month;
    int day;
    int hour;
    int minutes;
    struct tree_type *left;
    struct tree_type *right;
    
} tree_t;

tree_t *tree_create(char *filename, char *access, char *owner, char *size, int year, int month, int day, int hour, int minute);

void tree_free(tree_t *pt);

int cmp_filename(tree_t *pl, tree_t *pr);

int cmp_date(tree_t *pl, tree_t *pr);
 
#endif