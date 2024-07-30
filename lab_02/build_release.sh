#!/bin/bash

gcc -std=c99 -Wall -Werror -Wpedantic -Wextra -c main.c
gcc -std=c99 -Wall -Werror -Wpedantic -Wextra -c stud_funcs.c
gcc -std=c99 -Wall -Werror -Wpedantic -Wextra -c table_funcs.c
gcc -o app.exe main.o stud_funcs.o table_funcs.o
