#!/bin/bash

set -e

cd build

for i in 2 3 4 5 6 7 8 10 11; do
  echo $i RUN BEGIN =============================================
  valgrind -q --tool=massif --pages-as-heap=yes --massif-out-file=massif.out.$i ./qmem $i
  cat massif.out.$i | grep mem_heap_B | cut -f 2 -d "=" | sort -n | tail -n 1
done;

