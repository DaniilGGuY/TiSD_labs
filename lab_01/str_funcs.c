#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include "str_funcs.h"
#include "error.h"
#include "constant.h"

int read_string(FILE *f, char *str)
{
    char *p;
    
    if (!fgets(str, STR_LEN + 1, f))
        return ERR_IO;

    p = strchr(str, '\n');
    if (!p)
        return ERR_OVERFLOW;
        
    while (isspace(*p))
        --p;
    *(p + 1) = '\0';

    return OK;
}

bool is_correct_exp_val(const char *str, size_t *col_digit_m, size_t *col_digit_k)
{
    size_t i = 0;
    *col_digit_m = 0;
    *col_digit_k = 0;
    // Считываем пробельные символы перед числом
    while (isspace(str[i]))
        ++i;
    // Считываем знак числа
    if (str[i] == '+' || str[i] == '-')
        ++i;
    // Считываем незначащие нули
    while (str[i] == '0')
        ++i;
    if (!str[i])
        --i;
    if (str[i] == '.')
    {
        // Если у нас нет целой части, а сразу идет дробная
        ++i;
        // То у нас должна быть как минимум одна цифра, если нет, то число не в экспоненциальной форме
        if (!isdigit(str[i]))
            return false;
        // Считываем все цифры
        while (isdigit(str[i]))
        {
            ++i;       
            ++(*col_digit_m);
        }        
        // Если на этом строка заканчивается, то все в порядке
        if (!str[i])
            return true;
        // Но если у нас не конец строки, а все цифры считаны, то очередным символом может быть только e или E
        if (str[i] != 'e' && str[i] != 'E')
            return false;
        ++i;
        // Если у нас у экспоненты есть знак, то просто игнорируем его
        if (str[i] == '+' || str[i] == '-')
            ++i;
        // Теперь после экспоненты должна быть хотя бы одна цифра
        if (!isdigit(str[i]))
            return false;
        // Считываем все цифры
        while (isdigit(str[i]))
        {
            ++i;
            ++(*col_digit_k);
        }
        // Если на этом строка не заканчивается, то это не число в экспоненциальной форме записи
        if (str[i])
            return false;
        return true;
    }
    else if (isdigit(str[i]))
    {
        // Если у нас есть целая часть
        // Считываем целую часть
        while (isdigit(str[i]))
        {
            ++i;
            ++(*col_digit_m);
        }    
        
        // Если строка закончилась, то все ок, у нас обычное целое число
        if (!str[i])
            return true;
        // Если же строка не заканчивается, то нам надо прочитать дробную часть
        if (str[i] == '.')
        {
            ++i;
            // Учтем, что в дробной части может не быть ни одной цифры
            while (isdigit(str[i]))
            {
                ++i;
                ++(*col_digit_m);
            }
        }
        // Если строка закончилась, то все ок, у нас обычное вещественное число
        if (!str[i])
            return true;
        // Если же строка не закончилась, то у нас может быть единственный символ на этом месте - экспонента
        if (str[i] != 'e' && str[i] != 'E')
            return false;
        ++i;
        // Игнорируем знак
        if (str[i] == '+' || str[i] == '-')
            ++i;
        // Теперь после экспоненты должна быть хотя бы одна цифра
        if (!isdigit(str[i]))
            return false;
        // Считываем все цифры
        while (isdigit(str[i]))
        {
            ++i;
            ++(*col_digit_k);
        }
        // Если на этом строка не заканчивается, то это не число в экспоненциальной форме записи
        if (str[i])
            return false;
        return true;
    } 
    else
        return false;
}

bool is_correct_int_val(const char *str, size_t *col_digit)
{
    size_t i = 0;
    *col_digit = 0;
    // Считываем пробельные символы перед числом
    while (isspace(str[i]))
        ++i;
    // Считываем знак числа
    if (str[i] == '+' || str[i] == '-')
        ++i;
    // Считываем незначащие нули
    while (str[i] == '0')
        ++i;
    if (!str[i])
        --i;
    // Считываем само число
    while (isdigit(str[i]))
    {
        ++i;
        ++(*col_digit);
    }    
        
    // Если строка закончилась, то все ок, у нас обычное целое число
    if (!str[i])
        return true;
    // Если же строка не закончилась, то это не целое число
    return false;
}
