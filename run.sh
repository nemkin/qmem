#!/bin/bash

set -e

cd build
cmake -g -DCMAKE_BUILD_TYPE=Debug ../src
make
./qmem
