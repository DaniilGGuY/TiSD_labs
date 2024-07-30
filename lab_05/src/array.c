#include <stdlib.h>

#include "array.h"
#include "errors.h"

bool aqueue_is_empty(const array_t *q)
{
    return (q->tail == -1);
}

bool aqueue_is_full(const array_t *q)
{    
    return (q->tail == q->head - 1) || (q->head == 0 && q->tail == N - 1);
}

int aqueue_push(array_t *q, double item)
{
    int rc = OK;
    if (!aqueue_is_full(q))
    {
        if (aqueue_is_empty(q))
            q->head = q->tail = 0;
        else
        {
            if (q->tail == N - 1)
                q->tail = 0;
            else
                q->tail += 1;
        }

        q->arr[q->tail] = item;
    }
    else
        rc = ERR_FULL;

    return rc;
}

int aqueue_pop(array_t *q, double *item)
{
    int rc = OK;
    if (!aqueue_is_empty(q))
    {
        *item = q->arr[q->head];
        if (q->tail == q->head)
            q->head = q->tail = -1;
        else
        {
            if (q->head == N - 1)
                q->head = 0;
            else
                q->head += 1;
        }
    }
    else
        rc = ERR_EMPTY;

    return rc;
}