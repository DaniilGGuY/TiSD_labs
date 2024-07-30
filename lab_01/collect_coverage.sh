#!/bin/bash

cd func_tests/scripts || exit
./func_tests.sh
cd ../..
echo
echo "Checking coverage of tests"
gcov main.c
gcov airthmetic.c
./clean.sh
