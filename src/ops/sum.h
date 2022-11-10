#pragma once

#include "../core/op.h"

class Sum : public QOp {

private:
  index input_qubits;
  index output_qubits;

  index input_size;
  index output_size;

public:
  Sum(std::string name, index input_qubits, index output_qubits);

  virtual Amplitudes row(index i);
  virtual Amplitudes col(index j);

  virtual void apply(QRegisters& target, const std::vector<index>& target_regs);
  virtual void apply(QRegisters& target, const std::vector<index>& input_regs, const std::vector<index>& output_regs);
};
