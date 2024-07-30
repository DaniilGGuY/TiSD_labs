#ifndef LIST_H__
#define LIST_H__

#include <stdbool.h>

// Структура узла очереди
typedef struct node
{
    double item;
    struct node *next;
} node_t;

// Структура самой очереди
typedef struct list
{
    node_t *head;
    node_t *tail;
} list_t;

// Создание узла
node_t *node_create(double item);

// Очистка памяти из-под узла
void node_free(node_t *node);

// Создание очереди
list_t *lqueue_create(void);

// Уничтожение очереди
void lqueue_destroy(list_t *q);

// Удаление всех элементов из очереди
void lqueue_make_empty(list_t *q);

// Проверка очереди на пустоту
bool lqueue_is_empty(const list_t *q);

// Проверка очереди на заполненность
bool lqueue_is_full(const list_t *q);

// Добавление элемента в очередь
int lqueue_push(list_t *q, double item);

// Удаление элемента из очереди
int lqueue_pop(list_t *q, double *item);

#endif