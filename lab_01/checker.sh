#!/bin/bash

echo "BUILDING RELEASE..."
./build_release.sh
./func_tests/scripts/func_tests.sh
echo
./clean.sh

echo "BUILDING DEBUG WITH ASAN..."
./build_release.sh
./func_tests/scripts/func_tests.sh
echo
./clean.sh

echo "BUILDING DEBUG WITH MSAN..."
./build_release.sh
./func_tests/scripts/func_tests.sh
echo
./clean.sh

echo "BUILDING DEBUG WITH UBSAN..."
./build_release.sh
./func_tests/scripts/func_tests.sh
echo
./clean.sh

echo "BUILDING DEBUG..."
./build_release.sh
./func_tests/scripts/func_tests.sh
echo
./clean.sh

