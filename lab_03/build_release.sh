#!/bin/bash

gcc -std=c99 -Wall -Werror -Wpedantic -Wextra -c main.c
gcc -std=c99 -Wall -Werror -Wpedantic -Wextra -c default_matrix.c
gcc -std=c99 -Wall -Werror -Wpedantic -Wextra -c vector.c
gcc -o app.exe main.o default_matrix.o vector.o
