#!/bin/bash

clang -std=c99 -fsanitize=address -fno-omit-frame-pointer -g -c main.c
clang -std=c99 -fsanitize=address -fno-omit-frame-pointer -g -c str_funcs.c
clang -std=c99 -fsanitize=address -fno-omit-frame-pointer -g -c airthmetic.c
clang -fsanitize=address -fno-omit-frame-pointer -g -o app.exe main.o str_funcs.o airthmetic.o
