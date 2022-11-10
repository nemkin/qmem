#!/bin/bash

cd build
sizes="2 3 4 5 6 7"

for i in $sizes; do
  echo $i RUN BEGIN =============================================
  valgrind -q --tool=massif --massif-out-file=massif.out.$i ./qmem $i
done;

echo SUMMARY =============================================
for i in $sizes; do
  echo $i
  cat massif.out.$i | grep mem_heap_B | cut -f 2 -d "=" | sort -n | tail -n 1
done;

