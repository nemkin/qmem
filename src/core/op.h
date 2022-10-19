#pragma once

#include "reg.h"

#include <complex>
#include <vector>

#include "base.h"

class QOp {
private:
  int _qubits;

protected:
  std::string _name;

public:
  QOp(std::string name, int qubits);
  std::string name();
  int qubits();
  int size();

  virtual Amplitudes row(int i) = 0;
  virtual Amplitudes col(int j) = 0;

  std::vector<int> get_bit_mask_mapping(const QRegisters& target, const std::vector<int>& target_regs);
  std::vector<int> get_qubit_mapping(std::vector<int> bit_mask_map);

  virtual void apply(QRegisters& target, const std::vector<int>& target_regs);
};
