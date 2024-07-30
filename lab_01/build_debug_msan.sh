#!/bin/bash

clang -std=c99 -fsanitize=memory -fPIE -fno-omit-frame-pointer -g -c main.c
clang -std=c99 -fsanitize=memory -fPIE -fno-omit-frame-pointer -g -c str_funcs.c
clang -std=c99 -fsanitize=memory -fPIE -fno-omit-frame-pointer -g -c airthmetic.c
clang -fsanitize=memory -fPIE -pie -fno-omit-frame-pointer -g -o app.exe main.o airthmetic.o
