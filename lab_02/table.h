#ifndef TABLE_H__
#define TABLE_H__

#include "constant.h"
#include <stdio.h>

typedef struct house {
    char street[STREET_LEN + 1];
    size_t build_num;
    size_t flat_num;
} house_t;

typedef struct dormitory {
    size_t build_num;
    size_t flat_num;
} dormitory_t;

typedef struct rental {
    char street[STREET_LEN + 1];
    size_t build_num;
    size_t flat_num;
    size_t cost;
} rental_t;

typedef struct date {
    size_t year;
    size_t month;
    size_t day;
} date_t;

typedef union adress {
    house_t house;
    dormitory_t dorm;
    rental_t rent;
} adress_t;

typedef enum house_type { HOUSE, DORM, RENT } house_type_t;

typedef struct student {
    char surname[SURNAME_LEN + 1];
    char name[NAME_LEN + 1];
    char group[GROUP_LEN + 1];
    char gender[GENDER_LEN + 1];
    size_t age;
    double av_mark;
    date_t date;
    house_type_t type;
    adress_t adress;
} student_t;

typedef struct key {
    char surname[SURNAME_LEN + 1];
    size_t index;
} key_field_t;

#endif