#include "stud_funcs.h"
#include "error.h"
#include "constant.h"
#include <string.h>

int stud_read(FILE *f, student_t *stud)
{
    char buf[STR_LEN + 1];
    char *p;
    size_t words_col = 1;
    if (!fgets(buf, STR_LEN + 1, f))
        return ERR_IO;

    p = strchr(buf, '\n');
    if (!p)
        return ERR_LEN_STR;
 
    for (size_t i = 0; i < strlen(buf); ++i)
    {
        if (buf[i] == ' ')
            ++words_col;
    }

    switch (words_col)
    {
        case 9:
            sscanf(buf, "%s %s %s %s %zu %lf %zu.%zu.%zu %zu %zu", stud->surname, stud->name, stud->group, \
                    stud->gender, &stud->age, &stud->av_mark, &stud->date.day, &stud->date.month, &stud->date.year, \
                    &stud->adress.dorm.build_num, &stud->adress.dorm.flat_num);
            stud->type = DORM;
            break;
        case 10:
            sscanf(buf, "%s %s %s %s %zu %lf %zu.%zu.%zu %s %zu %zu", stud->surname, stud->name, stud->group, \
                    stud->gender, &stud->age, &stud->av_mark, &stud->date.day, &stud->date.month, &stud->date.year, \
                    stud->adress.house.street, &stud->adress.house.build_num, &stud->adress.house.flat_num);
            stud->type = HOUSE;
            break;
        case 11:
            sscanf(buf, "%s %s %s %s %zu %lf %zu.%zu.%zu %s %zu %zu %zu", stud->surname, stud->name, stud->group, \
                    stud->gender, &stud->age, &stud->av_mark, &stud->date.day, &stud->date.month, &stud->date.year, \
                    stud->adress.rent.street, &stud->adress.rent.build_num, &stud->adress.rent.flat_num, \
                    &stud->adress.rent.cost);
            stud->type = RENT;
            break;
        default:
            return ERR_IO;
    }

    return ERR_OK;
}

int stud_read_from_terminal(student_t *stud)
{
    char *p, tmp[3];
    size_t type;

    fgets(tmp, 3, stdin);
    printf("Input surname: ");
    if (!fgets(stud->surname, SURNAME_LEN + 1, stdin))
        return ERR_IO;

    p = strchr(stud->surname, '\n');
    if (!p)
        return ERR_LEN_FIELD;
    *p = '\0';

    printf("Input name: ");
    if (!fgets(stud->name, NAME_LEN + 1, stdin))
        return ERR_IO;

    p = strchr(stud->name, '\n');
    if (!p)
        return ERR_LEN_FIELD;
    *p = '\0';

    printf("Input group: ");
    if (!fgets(stud->group, GROUP_LEN + 1, stdin))
        return ERR_IO;

    p = strchr(stud->group, '\n');
    if (!p)
        return ERR_LEN_FIELD;
    *p = '\0';

    printf("Input gender: ");
    if (!fgets(stud->gender, GENDER_LEN + 1, stdin))
        return ERR_IO;

    p = strchr(stud->gender, '\n');
    if (!p)
        return ERR_LEN_FIELD;
    *p = '\0';
    
    printf("Input age: ");
    if (scanf("%zu", &stud->age) != 1)
        return ERR_IO;

    printf("Input average mark: ");
    if (scanf("%lf", &stud->av_mark) != 1 || stud->av_mark < 0 || stud->av_mark > 5)
        return ERR_IO;

    printf("Input year of admission: ");
    if (scanf("%zu", &stud->date.year) != 1)
        return ERR_IO;

    printf("Input month of admission: ");
    if (scanf("%zu", &stud->date.month) != 1)
        return ERR_IO;

    printf("Input day of admission: ");
    if (scanf("%zu", &stud->date.day) != 1)
        return ERR_IO;

    printf("Input type of home-place\n");
    printf("Input 0 if it is home, 1 if it is dormitory and 2 if it is rent home: ");
    if (scanf("%zu", &type) != 1)
        return ERR_IO;
    if (type == 0)
    {
        stud->type = HOUSE;
        fgets(tmp, 3, stdin);
        printf("Input street: ");
        if (!fgets(stud->adress.house.street, STREET_LEN + 1, stdin))
           return ERR_IO;

        p = strchr(stud->adress.house.street, '\n');
        if (!p)
            return ERR_LEN_FIELD;
        *p = '\0';

        printf("Input num of build: ");
        if (scanf("%zu", &stud->adress.house.build_num) != 1)
            return ERR_IO;

        printf("Input num of flat: ");
        if (scanf("%zu", &stud->adress.house.flat_num) != 1)
            return ERR_IO;
    }
    else if (type == 1)
    {
        stud->type = DORM;
        printf("Input num of build: ");
        if (scanf("%zu", &stud->adress.dorm.build_num) != 1)
            return ERR_IO;

        printf("Input num of flat: ");
        if (scanf("%zu", &stud->adress.dorm.flat_num) != 1)
            return ERR_IO;
    }
    else if (type == 2)
    {
        stud->type = RENT;
        fgets(tmp, 3, stdin);
        printf("Input street: ");
        if (!fgets(stud->adress.rent.street, STREET_LEN + 1, stdin))
           return ERR_IO;

        p = strchr(stud->adress.rent.street, '\n');
        if (!p)
            return ERR_LEN_FIELD;
        *p = '\0';

        printf("Input num of build: ");
        if (scanf("%zu", &stud->adress.rent.build_num) != 1)
            return ERR_IO;

        printf("Input num of flat: ");
        if (scanf("%zu", &stud->adress.rent.flat_num) != 1)
            return ERR_IO;

        printf("Input cost of rent: ");
        if (scanf("%zu", &stud->adress.rent.cost) != 1)
            return ERR_IO;
    }
    else
        return ERR_IO;

    return ERR_OK;
}

void stud_print(FILE *f, student_t *stud)
{
    if (stud->type == HOUSE)
        fprintf(f, "%s %s %s %s %zu %lf %zu.%zu.%zu %s %zu %zu\n", stud->surname, stud->name, stud->group, \
                    stud->gender, stud->age, stud->av_mark, stud->date.day, stud->date.month, stud->date.year, \
                    stud->adress.house.street, stud->adress.house.build_num, stud->adress.house.flat_num);
    else if (stud->type == DORM)
        fprintf(f, "%s %s %s %s %zu %lf %zu.%zu.%zu %zu %zu\n", stud->surname, stud->name, stud->group, \
                    stud->gender, stud->age, stud->av_mark, stud->date.day, stud->date.month, stud->date.year, \
                    stud->adress.dorm.build_num, stud->adress.dorm.flat_num);
    else if (stud->type == RENT)
        fprintf(f, "%s %s %s %s %zu %lf %zu.%zu.%zu %s %zu %zu %zu\n", stud->surname, stud->name, stud->group, \
                    stud->gender, stud->age, stud->av_mark, stud->date.day, stud->date.month, stud->date.year, \
                    stud->adress.rent.street, stud->adress.rent.build_num, stud->adress.rent.flat_num, \
                    stud->adress.rent.cost);
}
