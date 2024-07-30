#ifndef AIRTHMETIC_H__
#define AIRTHMETIC_H__

#include <stdbool.h>
#include <stdio.h>
#include "constant.h"

typedef struct real_t
{
    bool mant_sign;
    int mant[MANT_LEN];
    size_t mant_len;
    bool exp_sign;
    int exp;
} real_t;

typedef struct int_t
{
    bool sign;
    int mant[MANT_LEN];
    size_t mant_len;
} int_t;

void convert_real(const char *real_string, real_t *val);

void convert_int(const char *int_string, int_t *val);

int compare(const int arr1[], size_t n1, const int arr2[], size_t n2);

void subtraction(int arr1[], size_t *n1, const int arr2[], size_t n2);

int division(real_t *dividend, int_t *divider, real_t *res);

void print_res(real_t *res);

#endif
