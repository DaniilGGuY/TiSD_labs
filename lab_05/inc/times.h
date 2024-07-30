#ifndef RESEARCH_H__
#define RESEARCH_H__

// Структура, задающая параметры моделирования
typedef struct times
{
    double mint1;
    double maxt1;
    double mint2;
    double maxt2;
    double mint3;
    double maxt3;
    double mint4;
    double maxt4;
} times_t;

// Получение случайного времени, равного интервалу прихода заявки в первую очередь (Т1)
double get_times1(times_t *t);

// Получение случайного времени, равного интервалу приходы заявки в первую очередь (Т2)
double get_times2(times_t *t);

// Получение случайного времени, равного времени обработки заявки первого типа (Т3)
double get_times3(times_t *t);

// Получение случайного времени, равного времени обработки заявки второго типа (Т4)
double get_times4(times_t *t);

// Задание параметров моделирования вручную
void edit_times(times_t *t);

// Вывод парметров моделирования
void print_times(times_t *t);

#endif