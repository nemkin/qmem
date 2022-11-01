#pragma once

#include <complex>
#include <vector>
#include <map>

#include "base.h"

class QRegisters {

public:
  int total_qubits = 0;
  int total_size = 0;
  int total_registers = 0;
  std::vector<int> qubits;
  std::vector<int> sizes;
  std::vector<std::string> names;

  Amplitudes amplitudes;

  QRegisters();
  void Add(std::string name, int qubits, int initial = 0);
};
