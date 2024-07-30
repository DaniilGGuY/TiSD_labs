#include <string.h>
#include <stdlib.h>

#include "stack_list.h"
#include "errors.h"
#include "process_string.h"

void free_stack_list(stack_list_t *head)
{
    for ( ; head; )
    {
        stack_list_t *new_head = head->next;
        free(head);
        head = new_head;
    }
}

int pop_stack_list(stack_list_t **head, size_t *size)
{
    if (*size == 0)
        return ERR_EMPTY;

    stack_list_t *new_head = (*head)->next;
    printf("%p adress is empty\n", (void *)(*head));
    free(*head);
    *head = new_head;
    --(*size);
    return ERR_OK;
}

int push_stack_list(stack_list_t **head, size_t *size, char *str)
{
    if (*size == N)
        return ERR_OVERFLOW;

    stack_list_t *new_head = malloc(sizeof(stack_list_t));
    if (new_head)
    {
        strcpy(new_head->word, str);
        new_head->next = *head;
        *head = new_head;
        ++(*size);
    }
    else
        return ERR_MEM;
    
    return ERR_OK;
}

void print_stack_list(stack_list_t *head)
{
    printf("Stack list looks like:\n");
    while (head)
    {
        printf("| ");
        print_str(head->word);
        printf(" %p\n", (void *)head);
        head = head->next;
    }

    printf("---------------\n");
}

void print_res_stack_list(stack_list_t *head)
{
    printf("Stack list res:\n");
    while (head)
    {
        reverse_print_str(head->word);
        printf(" ");
        head = head->next;
    }

    printf("\n");
}
