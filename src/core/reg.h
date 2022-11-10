#pragma once

#include <complex>
#include <vector>
#include <map>

#include "amplitudes.h"

class QRegisters {

public:
  index total_qubits = 0;
  index total_size = 0;
  index total_registers = 0;
  std::vector<index> qubits;
  std::vector<index> sizes;
  std::vector<std::string> names;

  Amplitudes amplitudes;

  QRegisters();
  void Add(std::string name, index qubits, index initial = 0);
};
