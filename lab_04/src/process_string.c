#include <stdio.h>
#include <string.h>

#include "errors.h"
#include "constants.h"

int read_str(char *str)
{
    char *p;
    if (!fgets(str, WORD_LEN + 1, stdin))
        return ERR_IO;

    p = strchr(str, '\n');
    if (!p)
        return ERR_LEN;

    *p = 0;
    
    return ERR_OK;
}

void print_str(char *str)
{
    for (size_t i = 0; i < strlen(str); ++i)
        printf("%c", str[i]);
}

void reverse_print_str(char *str)
{
    for (int i = strlen(str) - 1; i >= 0; --i)
        printf("%c", str[i]);
}
