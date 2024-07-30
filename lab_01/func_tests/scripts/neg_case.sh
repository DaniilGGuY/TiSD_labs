#!/bin/bash

input="$1"
app="./app.exe"
res="res.txt"
"$app" < "$input" > "$res"

exit $?
