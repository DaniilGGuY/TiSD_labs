#ifndef STR_FUNCS_H__
#define STR_FUNCS_H__

#include <stdbool.h>

int read_string(FILE *f, char *str);

bool is_correct_exp_val(const char *str, size_t *col_digit_m, size_t *col_digit_k);

bool is_correct_int_val(const char *str, size_t *col_digit);

#endif
