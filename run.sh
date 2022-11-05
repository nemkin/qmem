#!/bin/bash

set -e

cd build
cmake -DCMAKE_BUILD_TYPE=Debug ../src
make

valgrind --tool=massif --pages-as-heap=yes --massif-out-file=massif.out ./qmem; grep mem_heap_B massif.out | sed -e 's/mem_heap_B=\(.*\)/\1/' | sort -g  | tail -n 1

