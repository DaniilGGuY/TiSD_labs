#include <stdlib.h>

#include "list.h"
#include "errors.h"

node_t *node_create(double item)
{
    node_t *new_el = malloc(sizeof(node_t));

    if (new_el)
    {
        new_el->item = item;
        new_el->next = NULL;
    }

    return new_el;
}

void node_free(node_t *node)
{
    free(node);
}

list_t *lqueue_create(void)
{
    list_t *new_q = malloc(sizeof(list_t));
    if (new_q)
    {
        new_q->head = NULL;
        new_q->tail = NULL;
    }

    return new_q;
}

void lqueue_destroy(list_t *q)
{
    lqueue_make_empty(q);
    free(q);
}

void lqueue_make_empty(list_t *q)
{
    double item;
    while (!lqueue_is_empty(q))
        (void)lqueue_pop(q, &item);
}

bool lqueue_is_empty(const list_t *q)
{
    return (q->head == NULL) && (q->tail == NULL);
}

bool lqueue_is_full(const list_t *q)
{
    return (q == NULL) && false;
}

int lqueue_push(list_t *q, double item)
{
    int rc = OK;
    if (!lqueue_is_full(q))
    {
        node_t *new_el = node_create(item);
        if (new_el)
        {
            if (lqueue_is_empty(q))
            {
                q->head = new_el;
                q->tail = new_el;
            }
            else
            {
                q->tail->next = new_el;
                q->tail = q->tail->next;
            }
        }
        else 
            rc = ERR_MEM;
    }
    else
        rc = ERR_FULL;

    return rc;
}

int lqueue_pop(list_t *q, double *item)
{
    int rc = OK;
    node_t *new_head = NULL;
    if (!lqueue_is_empty(q))
    {
        *item = q->head->item;
        new_head = q->head->next;
        if (q->head == q->tail)
            q->tail = new_head;
        node_free(q->head);
        q->head = new_head;
    }
    else
        rc = ERR_EMPTY;

    return rc;
}