#!/bin/bash

input="$1"
output="$2"
app="./app.exe"
res="res.txt"
"$app" < "$input" > "$res"
if ./func_tests/scripts/comparator.sh "$output" "$res"; then
  exit 1
else
  exit 0
fi
