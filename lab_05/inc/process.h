#ifndef PROCESS_H__
#define PROCESS_H__

#include "times.h"

// Вывод меню
void menu();

// Моделирование для очереди на списке
void process_list(times_t *pt);

// Моделирование для очереди на массиве
void process_array(times_t *pt, array_t *q_1, array_t *q_2);

// Исследование базовых операций для очереди-списка
void research_list();

// Исследование азовых операций для очереди-массива
void research_array();

#endif