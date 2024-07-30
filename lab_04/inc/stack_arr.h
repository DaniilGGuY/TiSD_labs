#ifndef STACK_ARR_H__
#define STACK_ARR_H__

#include <stdio.h>

#include "constants.h"

int pop_stack_arr(char stack[][WORD_LEN + 1], size_t *size);

int push_stack_arr(char stack[][WORD_LEN + 1], size_t *size, char *str);

void print_stack_arr(char stack[][WORD_LEN + 1], size_t size);

void print_res_stack_array(char stack[][WORD_LEN + 1], size_t size);

#endif