#ifndef STACK_LIST_H__
#define STACK_LIST_H__

#include <stdio.h>

#include "constants.h"

typedef struct stack_list
{
    char word[WORD_LEN + 1];
    struct stack_list *next;
} stack_list_t;

void free_stack_list(stack_list_t *head);

int pop_stack_list(stack_list_t **head, size_t *size);

int push_stack_list(stack_list_t **head, size_t *size, char *str);

void print_stack_list(stack_list_t *head);

void print_res_stack_list(stack_list_t *head);

#endif