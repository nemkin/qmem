project ("qmem")

cmake_minimum_required (VERSION 3.12)

set(SOURCES
  "main.cpp"
  "core/op.cpp"
  "core/reg.cpp"
  "core/log.cpp"
  "ops/hadamard.cpp"
  "ops/grover.cpp"
)

add_executable (qmem ${SOURCES} "ops/transposed.cpp")
set_property(TARGET qmem PROPERTY CXX_STANDARD 20)
