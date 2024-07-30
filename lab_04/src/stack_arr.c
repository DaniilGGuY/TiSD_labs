#include <string.h>

#include "stack_arr.h"
#include "errors.h"
#include "process_string.h"

int pop_stack_arr(char stack[][WORD_LEN + 1], size_t *size)
{
    if (*size == 0)
        return ERR_EMPTY;

    memset(stack[*size - 1], 0, sizeof(stack[*size - 1]));
    --(*size);
    return ERR_OK;
}

int push_stack_arr(char stack[][WORD_LEN + 1], size_t *size, char *str)
{
    if (*size == N)
        return ERR_OVERFLOW;

    strcpy(stack[*size], str);
    ++(*size);
    return ERR_OK;
}

void print_stack_arr(char stack[][WORD_LEN + 1], size_t size)
{
    printf("Stack array looks like:\n");
    for (int i = size - 1; i >= 0; --i)
    {
        printf("| ");
        print_str(stack[i]);
        printf("\n");
    }

    printf("---------------\n");
}

void print_res_stack_array(char stack[][WORD_LEN + 1], size_t size)
{
    printf("Stack array res:\n");
    for (int i = size - 1; i >= 0; --i)
    {
        reverse_print_str(stack[i]);
        printf(" ");
    }

    printf("\n");
}
