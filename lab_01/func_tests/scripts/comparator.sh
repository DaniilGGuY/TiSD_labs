#!/bin/bash

IFS=' '
num1=0
flag2=0
while read -r x; do
  if [[ $x =~ "Result:" ]]; then
    break
  fi
  num1=$((num1 + 1))
done < "$1"
cur1=0
pos1=0
while read -r x; do
  if [[ "$cur1" -eq "$num1" ]]; then
    for ((i=7;i<=${#x};i++)); do
      if [[ ${x:$i-7:7} == "Result:" ]]; then
        pos1=$i
      fi
    done
    break
  fi
  cur1=$((cur1 + 1))
done < "$1"
num2=0
while read -r y; do
  if [[ $y =~ "Result:" ]]; then
    break
  fi
  num2=$((num2 + 1))
done < "$2"
cur2=0
pos2=0
while read -r y; do
  if [[ "$cur2" -eq "$num2" ]]; then
    for ((i=7;i<=${#y};i++)); do
      if [[ ${y:$i-7:7} == "Result:" ]]; then
        pos2=$i
      fi
    done
    break
  fi
  cur2=$((cur2 + 1))
done < "$2"
num=0
flag1=0
arr1=()
while read -r x; do
  if [[ flag1 -eq 0 ]] && [[ num -lt num1 ]]; then
    num=$((num+1))
    continue
  elif [[ flag1 -eq 0 ]] && [[ num -eq num1 ]]; then
    flag1=1
    read -r -a arr1 <<< "${x:pos1}"
    continue
  fi
  read -r -a arr1 <<< "$x"
done <"$1"
num=0
flag2=0
arr2=()
while read -r y; do
  if [[ flag2 -eq 0 ]] && [[ num -lt num2 ]]; then
    num=$((num+1))
    continue
  elif [[ flag2 -eq 0 ]] && [[ num -eq num2 ]]; then
    flag2=1
    read -r -a arr2 <<< "${y:pos2}"
    continue
  fi
  read -r -a arr2 <<< "$y"
done < "$2"
if [[ "${arr1[*]}" == "${arr2[*]}" ]]; then
  exit 0
else
  exit 1
fi
