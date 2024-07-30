#include <stdio.h>
#include <string.h>
#include "airthmetic.h"
#include "error.h"
#include "constant.h"
#include "str_funcs.h"

int main(void)
{
    real_t real_val;
    real_t res;
    int_t int_val;
    char first_num[STR_LEN + 1];
    char second_num[STR_LEN + 1];
    size_t len_first_m, len_first_k, len_second;
    int rc = OK;
    
    printf("This program divides a real number by an integer\n");
    printf("Real num inputs with format [+-]m.nЕ[+-]K, where m+n <= 35 and K <= 5\n");
    printf("Integer num inputs with 35 or less significant digits\n");
    printf("Enter real num:\n");
    printf("----5---10---15---20---25---30---35---40---45---50\n");
    rc = read_string(stdin, first_num);
    if (!rc)
    {
        if (is_correct_exp_val(first_num, &len_first_m, &len_first_k))
        {
            printf("Enter int num:\n");
            rc = read_string(stdin, second_num);
            if (!rc)
            {
                if (is_correct_int_val(second_num, &len_second))
                {
                    if (len_first_k <= 5 && len_first_m <= 35 && len_second <= 35)
                    {
                        convert_real(first_num, &real_val);
                        convert_int(second_num, &int_val);
                        if (int_val.mant[0] == 0)
                        {
                            rc = ERR_RES;
                            printf("Reached machine zero or infinity");
                        }
                        else
                        {
                            rc = division(&real_val, &int_val, &res);
                            if (res.exp > 99999 || res.exp < -99999)
                            {
                                rc = ERR_ANS;
                                printf("There is overflow of exp");
                            }
                            else
                            {
                                if (!rc)
                                {
                                    printf("Result: ");
                                    print_res(&res);
                                }
                                else
                                    printf("Reached machine zero or infinity");
                            }
                        }
                    }
                    else
                    {
                        rc = ERR_LEN;
                        printf("To many digits");
                    } 
                }
                else
                {
                    rc = ERR_INT;
                    printf("Error with input int value. Its not int");
                }
            }
            else
            {
                if (rc == ERR_IO)
                    printf("Incorrect input string");
                else if (rc == ERR_OVERFLOW)
                    printf("Incorrect len of input string");
            }
        }
        else
        {
            rc = ERR_EXP;
            printf("Error with input exp value. Its not exp");
        }
    }
    else
    {
        if (rc == ERR_IO)
            printf("Incorrect input string");
        else if (rc == ERR_OVERFLOW)
            printf("Incorrect len of input string");
    }
    
    return rc;
}

