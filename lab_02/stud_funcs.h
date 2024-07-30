#ifndef STUD_FUNCS_H__
#define STUD_FUNCS_H__

#include <stdio.h>
#include "table.h"

int stud_read(FILE *f, student_t *stud);

int stud_read_from_terminal(student_t *stud);

void stud_print(FILE *f, student_t *stud);

#endif