#ifndef ARRAY_H__
#define ARRAY_H__

#include <stdbool.h>

#define N       1000

typedef struct array
{
    double arr[N];
    int head;
    int tail;
} array_t;

// Проверяет очередь на пустоту
bool aqueue_is_empty(const array_t *q);

// Проверяет очередь на заполненность
bool aqueue_is_full(const array_t *q);

// Добавляет в очередь элемент
int aqueue_push(array_t *q, double item);

// Удаляет из очереди элемент
int aqueue_pop(array_t *q, double *item);

#endif