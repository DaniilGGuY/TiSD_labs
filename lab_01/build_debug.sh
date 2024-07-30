#!/bin/bash

gcc -std=c99 -Wall -Werror -Wpedantic -Werror -Wfloat-equal -Wfloat-conversion -g -c main.c
gcc -std=c99 -Wall -Werror -Wpedantic -Werror -Wfloat-equal -Wfloat-conversion -g -c str_funcs.c
gcc -std=c99 -Wall -Werror -Wpedantic -Werror -Wfloat-equal -Wfloat-conversion -g -c airthmetic.c
gcc -g -o app.exe main.o str_funcs.o airthmetic.o
