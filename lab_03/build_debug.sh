#!/bin/bash

gcc -std=c99 -Wall -Werror -Wpedantic -Wextra -g -c main.c
gcc -std=c99 -Wall -Werror -Wpedantic -Wextra -g -c default_matrix.c
gcc -std=c99 -Wall -Werror -Wpedantic -Wextra -g -c vector.c
gcc -g -o app.exe main.o default_matrix.o vector.o
