#pragma once

#include <complex>
#include <vector>

#include "base.h"
#include "reg.h"

class QOp {
 private:
  index _qubits;

 protected:
  std::string _name;
  index count_set_bits(index n);

 public:
  QOp(std::string name, index qubits);
  std::string name();
  index qubits();
  index size();

  virtual Amplitudes row(index i) = 0;
  virtual Amplitudes col(index j) = 0;

  std::vector<index> get_bit_mask_mapping(
      const QRegisters& target, const std::vector<index>& target_regs);
  std::vector<index> get_qubit_mapping(std::vector<index> bit_mask_map);

  virtual void apply(QRegisters& target, const std::vector<index>& target_regs);
};
