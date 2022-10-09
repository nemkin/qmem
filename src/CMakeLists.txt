project ("qmem")

cmake_minimum_required (VERSION 3.12)

set(SOURCES
  main.cpp
  qmem/qmem.cpp
)

add_executable (qmem ${SOURCES})
set_property(TARGET qmem PROPERTY CXX_STANDARD 20)
