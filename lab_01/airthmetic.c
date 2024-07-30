#include "airthmetic.h"
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include "error.h"

void convert_real(const char *real_string, real_t *val)
{
    size_t n = strlen(real_string), i = 0, col_digit_m = 0, int_part = 0;
    val->exp_sign = 0;
    val->mant_sign = 0;
    val->exp = 0;
    while (isspace(real_string[i]))
        ++i;

    if (real_string[i] == '+')
    {
        ++i;
        val->mant_sign = 0;
    } 
    else if (real_string[i] == '-')
    {
        ++i;
        val->mant_sign = 1;
    }
    while (real_string[i] == '0')
        ++i;

    if (real_string[i] == '.')
    {
        ++i;
        while (isdigit(real_string[i]))
        {
            val->mant[col_digit_m] = real_string[i] - '0';
            ++col_digit_m;
            ++i;
        }        

        if (i < n)
        {
            ++i;
            
            if (real_string[i] == '+')
            {
                ++i;
                val->exp_sign = 0;
            } 
            else if (real_string[i] == '-')
            {
                ++i;
                val->exp_sign = 1;
            }

            while (isdigit(real_string[i]))
            {
                ++i;
                val->exp = val->exp * 10 + real_string[i] - '0';
            }
        }
    }
    else if (isdigit(real_string[i]))
    {
        while (isdigit(real_string[i]))
        {
            val->mant[col_digit_m] = real_string[i] - '0';
            ++col_digit_m;
            ++int_part;
            ++i;
        }    

        if (i < n)           
        {
            if (real_string[i] == '.')
            {
                ++i;
                while (isdigit(real_string[i]))
                {
                    val->mant[col_digit_m] = real_string[i] - '0';
                    ++col_digit_m;
                    ++i;
                }
            }
            
            if (i < n)
            {
                ++i;
                
                if (real_string[i] == '+')
                {
                    ++i;
                    val->exp_sign = 0;
                } 
                else if (real_string[i] == '-')
                {
                    ++i;
                    val->exp_sign = 1;
                }

                while (isdigit(real_string[i]))
                {
                    val->exp = val->exp * 10 + real_string[i] - '0';
                    ++i;
                }
            }
        }
    }

    if (val->exp_sign == 0)
        val->exp += int_part;
    else
    {
        val->exp = -val->exp + int_part;
        val->exp_sign = (val->exp < 0);
    }

    val->mant_len = col_digit_m;
}

void convert_int(const char *int_string, int_t *val)
{
    size_t i = 0, col_digit = 0;
    val->sign = 0;
    while (isspace(int_string[i]))
        ++i;

    if (int_string[i] == '+')
    {
        ++i;
        val->sign = 0;
    } 
    else if (int_string[i] == '-')
    {
        ++i;
        val->sign = 1;
    }
    while (int_string[i] == '0')
        ++i;

    while (isdigit(int_string[i]))
    {
        val->mant[col_digit] = int_string[i] - '0';
        ++col_digit;
        ++i;
    }
    
    val->mant_len = col_digit;
}

int compare(const int arr1[], size_t n1, const int arr2[], size_t n2)
{
    if (n1 < n2)
        return -1;
    else if (n1 > n2)
        return 1;
    
    for (size_t i = 0; i < n1; ++i)
    {
        if (arr1[i] > arr2[i])
            return 1;
        else if (arr1[i] < arr2[i])
            return -1;
    }
    
    return 0;
}

void subtraction(int arr1[], size_t *n1, const int arr2[], size_t n2)
{
    size_t pos = 0;
    int el = 0;
    for (size_t i = 0; i < *n1; ++i)
    {
        el = (i < n2) ? arr2[n2 - 1 - i] : 0;
        if (arr1[*n1 - 1 - i] < el)
        {
            arr1[*n1 - 1 - i] = 10 + arr1[*n1 - 1 - i] - el;
            arr1[*n1 - 2 - i] -= 1;
        }
        else
            arr1[*n1 - 1 - i] -= el;
    }
    
    if (arr1[0] == 0)
    {
        while (pos < *n1 && arr1[pos] == 0)
            ++pos;
        
        if (pos < *n1)
            for (size_t i = pos; i < *n1; ++i)
                arr1[i - pos] = arr1[i];

        *n1 -= pos;
    }
}   

void print_arr(int arr[], size_t n)
{
    for (size_t i = 0; i < n; ++i)
        printf("%d", arr[i]);
    printf("\n");
}

int division(real_t *dividend, int_t *divider, real_t *res)
{
    int part[MANT_LEN + 1];
    int ans[MANT_LEN + 1];
    size_t n1 = dividend->mant_len, n2 = divider->mant_len;
    size_t n = (n1 < n2) ? n1 : n2, digits_used = 0;
    int num_reps = 0;
    bool is_correct_ans = 0, flag = 0;

    res->mant_sign = (dividend->mant_sign != divider->sign);
    res->mant_len = 0;
    res->exp = dividend->exp - n + 1;
    for (size_t i = 0; i < n; ++i, ++digits_used)
        part[i] = dividend->mant[i];
    
    if (compare(part, n, divider->mant, n2) == -1 && n2 < n1)
    {
        part[n] = dividend->mant[n];
        ++n;
        ++digits_used;
        --res->exp;
    }
    
    while (res->mant_len < MANT_LEN + 1 && (n || digits_used < n1))
    {
        if (compare(part, n, divider->mant, n2) == -1)
        {
            if (digits_used < n1)
                part[n] = dividend->mant[digits_used++];
            else
                part[n] = 0;
            ++n;
            if (res->mant_len && !flag)
                ans[res->mant_len++] = 0;
            else if (!res->mant_len)
                res->exp -= 1;

            flag = 0;
        }
        else
        {
            while (compare(part, n, divider->mant, n2) >= 0)
            {
                //print_arr(part, n);
                ++num_reps;
                subtraction(part, &n, divider->mant, n2);
                if (num_reps > 9)
                    return ERR_RES;
            }
            //printf("REPS: %d %zu %zu\n", num_reps, res->mant_len, n);
            ans[res->mant_len] = num_reps;
            ++res->mant_len;
            //print_arr(ans, res->mant_len);
            num_reps = 0;
            flag = 1;
        }
    }

    for (size_t i = 0; i < res->mant_len; ++i)
        if (ans[i])
            is_correct_ans = 1;

    if (!is_correct_ans && res->mant_len == MANT_LEN + 1)
        return ERR_RES;
    if (res->mant_len == MANT_LEN + 1)
    {
        if (ans[res->mant_len - 1] >= 5)
        {
            bool is = 1;
            for (int i = res->mant_len - 2; i >= 0; --i)
            {
                ans[i] += is;
                is = ans[i] > 9;
                ans[i] %= 10;
            }

            if (is)
            {
                for (size_t i = res->mant_len - 2; i > 0; --i)
                    ans[i] = ans[i - 1];
                ans[0] = is;
            }
        }

        --res->mant_len;
    }

    while (ans[res->mant_len - 1] == 0)
        --res->mant_len;

    for (size_t i = 0; i < res->mant_len; ++i)
        res->mant[i] = ans[i];

    return OK;
}

void print_res(real_t *res)
{
    if (res->mant_sign)
        printf("-");
    printf("0.");
    for (size_t i = 0; i < res->mant_len; ++i)
        printf("%d", res->mant[i]);
    printf("E");
    printf("%d\n", res->exp);
}
