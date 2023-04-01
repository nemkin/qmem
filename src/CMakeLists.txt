project ("qmem")

cmake_minimum_required (VERSION 3.12)

set(SOURCES
  "main.cpp"
  "core/op.cpp"
  "core/reg.cpp"
  "core/log.cpp"
  "core/amplitudes.cpp"
  "ops/hadamard.cpp"
  "ops/grover.cpp"
  "ops/sum.cpp"
  "ops/mcnot.cpp"
  "ops/transposed.cpp"
  "ops/shift.cpp"
  "ops/single.cpp"
  "ops/tensored.cpp"
  "ops/added.cpp"
)

add_executable (qmem ${SOURCES})
set_property(TARGET qmem PROPERTY CXX_STANDARD 20)
