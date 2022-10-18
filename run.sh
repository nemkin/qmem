#!/bin/bash

set -e

cd build
cmake -DCMAKE_BUILD_TYPE=Debug ../src
make
./qmem
