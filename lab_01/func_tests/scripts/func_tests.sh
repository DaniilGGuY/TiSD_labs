#!/bin/bash

count=0

for file in ./func_tests/data/*_in.txt; do
  if [[ "$file" =~ pos_[0-9][0-9]_in\.txt ]]; then
    echo Checking "$file"...
    num=$(echo "$file" | grep -o "[0-9][0-9]")
    output=$(find ./func_tests/data/ -name "pos_$num\_out\.txt")
    if ./func_tests/scripts/pos_case.sh "$file" "$output"; then
      echo Test pos_"$num" is incorrect
      count=$((count+1))
    else
      echo All is OK
    fi
  elif [[ "$file" =~ neg_[0-9][0-9]_in\.txt ]]; then
    echo Checking "$file"...
    num=$(echo "$file" | grep -o "[0-9][0-9]")
    if ./func_tests/scripts/neg_case.sh "$file"; then
      echo Test neg_"$num" incorrect
      count=$((count+1))
    else
      echo All is OK
    fi
  fi
done

echo Fails: "$count"
exit $count
